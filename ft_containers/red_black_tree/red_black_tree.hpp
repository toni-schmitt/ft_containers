#pragma once

#include <memory>
#include "node.hpp"


namespace ft
{

	template < class T, class Alloc >
	class rbt_inserter;

	template < class T, class Alloc >
	class rbt_eraser;

	template < class T, class Alloc = std::allocator<T> >
	class red_black_tree
	{
		friend class rbt_inserter<T, Alloc>;

		friend class rbt_eraser<T, Alloc>;

		/* Member Types */
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

	private:
		typedef rbt_node<value_type, allocator_type> node_type;
		typedef typename node_type::node_ref node_ref;
		typedef typename node_type::const_node_ref const_node_ref;
		typedef typename node_type::node_ptr node_ptr;
		typedef typename node_type::const_node_ptr const_node_ptr;
		typedef typename node_type::node_color node_color;
		typedef rbt_inserter<value_type, allocator_type> inserter_type;
		typedef rbt_eraser<value_type, allocator_type> eraser_type;
		typedef enum { left_rotation = 0, right_rotation = 1 } rotate_direction;

		/* Private Members */
	private:
		node_ptr _root;
		inserter_type _inserter;
		eraser_type _eraser;

		/* Constructor */
	public:
		red_black_tree() : _inserter(inserter_type(*this)), _eraser(eraser_type(*this))
		{
			this->_root = NULL;
		}

		explicit red_black_tree(const value_type &key) : _inserter(inserter_type(*this)), _eraser(eraser_type(*this))
		{
			this->_root = this->insert(key);
		}

		/* Public Member Functions */

		/* Modifiers Functions */
	public:
		inline void insert(const value_type &data)
		{
			if (this->_root == NULL)
			{
				this->_root = new node_type(NULL, data);
				this->_root->set_color(node_type::black);
				return;
			}

			this->_inserter.insert(data);
		}

		inline void erase(const value_type &data)
		{
			this->_eraser.erase(data);
		}

		/* Private Member Functions */
	private:
		/* Modifiers Functions */
		/**
		 * @brief Rotates the Red Black Tree at node in direction
		 * @param node Node to Rotate at
		 * @param direction Direction in which to rotate
		 */
		void _rotate(node_ptr node, rotate_direction direction)
		{
			if (node == NULL)
				return;

			node_ptr &to_rotate = node;

			node_ptr to_rotate_parent = to_rotate->get_parent();

			node_ptr to_rotate_left_child = to_rotate->get_left_child();

			// Reset Right Child of to_rotate
			to_rotate->reset_right_child();

			// Set Node's Parent to to_rotate_left_child
			if (to_rotate_parent == NULL)
				this->_root = to_rotate_left_child;
			else if (to_rotate_parent->get_left_child() == to_rotate)
				to_rotate_parent->set_left_child(to_rotate_left_child);
			else if (to_rotate_parent->get_right_child() == to_rotate)
				to_rotate_parent->set_right_child(to_rotate_left_child);

//			if (to_rotate_left_child == NULL)
//			{
//				to_rotate->set_parent(NULL);
//				return;
//			}
			// TODO: Do not use variables for this, use static accessing via ->
			// Set Parent of to_rotate_left_child to Node's Parent
			to_rotate->get_left_child()->set_parent(to_rotate_parent);
			switch (direction)
			{
				case left_rotation:
					// Set left child of to_rotate_left_child to to_rotate
					to_rotate->get_left_child()->set_left_child(to_rotate);
					break;
				case right_rotation:
					// Set right child of to_rotate_left_child to to_rotate
					to_rotate->get_left_child()->set_right_child(to_rotate);
					break;
			}
			// Set to_rotate's Parent to to_rotate_left_child
			to_rotate->set_parent(to_rotate_left_child);
		}

	};

} // namespace ft

#include "rbt_inserter.hpp"
#include "rbt_eraser.hpp"