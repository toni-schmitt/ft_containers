#pragma once

#include <memory>
#include "node.hpp"


namespace ft
{

	template < class T, class Alloc >
	class rbt_inserter;

	template < class T, class Alloc >
	class rbt_eraser;

	template < class T, class Alloc >
	class rbt_traverser;

	template < class T, class Alloc = std::allocator<T> >
	class red_black_tree
	{
		friend class rbt_inserter<T, Alloc>;

		friend class rbt_eraser<T, Alloc>;

		friend class rbt_traverser<T, Alloc>;

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
		typedef rbt_nil_node<value_type, allocator_type> nil_node_type;
		typedef rbt_inserter<value_type, allocator_type> inserter_type;
		typedef rbt_traverser<value_type, allocator_type> traverser_type;
		typedef rbt_eraser<value_type, allocator_type> eraser_type;

		/* Private Members */
	private:
		node_ptr _root;
		inserter_type _inserter;
		eraser_type _eraser;
		traverser_type _traverser;

		/* Constructor */
	public:
		red_black_tree(
				const allocator_type &alloc = allocator_type()
		) : _inserter(inserter_type(*this)), _eraser(eraser_type(*this)), _traverser(*this)
		{
			( void ) alloc;
			this->_root = NULL;
		}

		explicit red_black_tree(
				const value_type &key, const allocator_type &alloc = allocator_type()
		) : _inserter(inserter_type(*this)), _eraser(eraser_type(*this)), _traverser(*this)
		{
			( void ) alloc;
			this->_root = this->insert(key);
		}

		/* Exceptions */
	public:
		struct end_of_tree_exception : public std::exception
		{
			virtual const char *what() const throw() { return "End of Tree reached"; }
		};

		/* Public Member Functions */

		/* Traversal Functions */
	public:
		inline value_type get_next_key()
		{
			node_ptr next_node = this->_traverser.get_next_node();
			if (next_node == NULL)
				throw end_of_tree_exception();
			return next_node->get_key();
		}

		/* Modifiers Functions */
	public:
		inline void insert(const value_type &key)
		{
			if (this->_root == NULL)
			{
				this->_root = _new_node(NULL, key);
				this->_root->set_color(node_type::BLACK);
				return;
			}

			if (!this->_inserter.insert(key))
			{
				// Node is already in Tree
				return;
			}
		}

		inline void erase(const value_type &key)
		{
			this->_eraser.erase(key);
		}

		/* Private Member Functions */
	private:
		bool _is_nil_node(const node_ptr node)
		{
			node_ptr res = dynamic_cast<nil_node_type *>(node);
			if (res != NULL)
			{
				std::cout << "node is nil node" << std::endl;
				return true;
			}
			return false;
		}

		bool _is_root_node(node_ptr node)
		{
//			if (node != this->_root)
//				return false;
//			return true;
			return node == this->_root;
		}

		node_ptr _new_node(node_ptr parent, value_type key, node_color color = node_type::BLACK,
						   node_ptr left_child = NULL, node_ptr right_child = NULL)
		{
			node_ptr new_node = new node_type(parent, key, color, left_child, right_child);
			return new_node;
		}

		node_ptr _new_nil_node()
		{
			node_ptr new_nil_node = new nil_node_type();
			return new_nil_node;
		}

		/* Modifiers Functions */
		/**
		 * @brief Rotates the Red Black Tree at node in direction
		 * @param node Node to Rotate at
		 * @param direction Direction in which to rotate
		 */
		void _left_rotation(node_ptr node)
		{
			if (node == NULL)
				return;

			node_ptr parent = node->get_parent();
			node_ptr right_child = node->get_right_child();

			// Update node
			// 1. Update right child
			node->set_right_child(right_child->get_left_child());
			if (right_child->get_left_child() == NULL)
				node->reset_right_child();
			// 2. Update Parent
			if (parent == NULL)
			{
				this->_root = right_child;
				right_child->reset_parent();
				node->set_parent(right_child);
			}
			else
			{
				if (parent->get_left_child() == node)
				{
					parent->set_left_child(right_child);
				}
				else if (parent->get_right_child() == node)
				{
					parent->set_right_child(right_child);
				}
				node->set_parent(right_child);
				right_child->set_parent(parent);
			}

			// 3. Update right_child
			node_ptr right_child_left_child = right_child->get_left_child();

			right_child->set_left_child(node);
			if (right_child_left_child != NULL)
				right_child_left_child->set_parent(node);

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
#include "rbt_traverser.hpp"