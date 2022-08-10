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
		void _left_rotation(node_ptr node)
		{
			(void)node;
			throw std::logic_error("Not Implemented Exception");
		}

		void _right_rotation(node_ptr node)
		{
			if (node == NULL)
				return;

			node_ptr parent = node->get_parent();

			node_ptr left_child = node->get_left_child();

			// Update node
			// 1. Update Left Child
			node->set_left_child(left_child->get_right_child());
			if (left_child->get_right_child() == NULL)
				node->reset_left_child();
			// 2. Update Parent
			if (node->get_parent() == NULL)
			{
				// node is root node
				this->_root = left_child;
				left_child->reset_parent();
				node->set_parent(left_child);
			}
			else
			{
				if (parent->get_left_child() == node)
				{
					parent->set_left_child(left_child);
				}
				else if (parent->get_right_child() == node)
				{
					parent->set_right_child(left_child);
				}
				node->set_parent(left_child);
				left_child->set_parent(parent);
			}

			// 3. Update left_child
			node_ptr left_child_right_child = left_child->get_right_child();

			left_child->set_right_child(node);
			if (left_child_right_child != NULL)
				left_child_right_child->set_parent(node);

		}

	};

} // namespace ft

#include "rbt_inserter.hpp"
#include "rbt_eraser.hpp"