#pragma once

#include <memory>
#include "node.hpp"

namespace ft
{


	template < class T, class Alloc = std::allocator<T> >
	class red_black_tree
	{

		/* Member Types */
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

	protected:
		typedef rbt_node<value_type, allocator_type> node_type;
		typedef typename node_type::node_ref node_ref;
		typedef typename node_type::const_node_ref const_node_ref;
		typedef typename node_type::node_ptr node_ptr;
		typedef typename node_type::const_node_ptr const_node_ptr;
		typedef typename node_type::node_color node_color;
		typedef rbt_nil_node<value_type, allocator_type> nil_node_type;

		/* Private Members */
	private:
		node_ptr _root;
		allocator_type _alloc;


		/* Constructor */
	public:
		red_black_tree(
				const allocator_type &alloc = allocator_type()
		) : _alloc(alloc)
		{
			this->_root = NULL;
		}

		explicit red_black_tree(
				const value_type &key, const allocator_type &alloc = allocator_type()
		) : _alloc(alloc)
		{
			this->_root = this->insert(key);
		}

		~red_black_tree()
		{
			this->clear();
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
		inline void reset_traversal() const
		{
			this->_last_visited_node(NULL, true);
		}

		inline value_type get_next_key() const
		{
			node_ptr next_node = this->_get_next_node();
			if (next_node == NULL)
				throw end_of_tree_exception();
			return next_node->get_key();
		}

		inline value_type get_last_key() const
		{
			node_ptr last_node = this->_get_last_node();
			if (last_node == NULL)
				throw end_of_tree_exception();
			return last_node->get_key();
		}

	private:

		node_ptr _get_next_node(bool reset = false) const
		{

			if (reset)
				this->reset_traversal();

			node_ptr next_node = _get_next_node(_last_visited_node());
			if (this->_is_nil_node(next_node))
				return NULL; // TODO: Better thing to return here
			_last_visited_node(next_node);
			return next_node;
		}

		node_ptr _get_last_node(bool reset = false) const
		{
			if (reset)
				this->reset_traversal();

			if (_last_visited_node() == NULL)
				return NULL; // TODO: Better thing to return here
			node_ptr last_node = _get_last_node(_last_visited_node());
			if (this->_is_nil_node(last_node))
				return NULL; // TODO: Better thing to return here
			_last_visited_node(last_node);
			return last_node;
		}

		node_ptr _get_last_node(node_ptr last_visited_node) const
		{

			if (last_visited_node->has_left_child())
			{
				node_ptr left_child = last_visited_node->get_left_child();

				if (left_child->has_right_child())
				{
					node_ptr right_child = left_child->get_right_child();
					if (right_child->get_key() < last_visited_node->get_key())
					{
						return _get_right_most_child(right_child);
					}
				}

				if (left_child->get_key() < last_visited_node->get_key())
					return left_child;
			}

			node_ptr current_node = last_visited_node;
			while (current_node)
			{
				if (current_node->get_key() < last_visited_node->get_key())
					return current_node;
				current_node = current_node->get_parent();
			}
			return NULL;
		}

		node_ptr &_last_visited_node(node_ptr set = NULL, bool reset = false) const
		{
			static node_ptr last_visited_node = NULL;

			if (reset)
				last_visited_node = NULL;
			if (set != NULL)
				last_visited_node = set;
			return last_visited_node;
		}

		node_ptr _get_left_most_child(node_ptr node) const
		{
			node_ptr current_node = node;
			while (current_node->get_left_child())
				current_node = current_node->get_left_child();
			return current_node;
		}

		node_ptr _get_left_most_child() const
		{
			return _get_left_most_child(this->_root);
		}

		node_ptr _get_right_most_child(node_ptr node) const
		{
			node_ptr current_node = node;
			while (current_node->get_right_child())
				current_node = current_node->get_right_child();
			return current_node;
		}

		bool _is_right_child(node_ptr node) const
		{
			if (!node->has_parent())
				return false;
			if (!node->get_parent()->has_right_child())
				return false;
			if (node != node->get_parent()->get_right_child())
				return false;
			return true;
			return node == node->get_parent()->get_right_child();
		}

		bool _is_left_child(node_ptr node) const
		{
			if (!node->get_parent())
				return false;
			if (!node->get_parent()->has_left_child())
				return false;
			if (node != node->get_parent()->get_left_child())
				return false;
			return true;
		}

		node_ptr _get_next_node(node_ptr last_visited_node) const
		{

			/*
			 * If last_visited_node is NULL, Tree has not been traversed
			 * Tree Traversal always starts (in in-Order Traversal) at left most child
			 */
			if (last_visited_node == NULL)
			{
				return _get_left_most_child();
			}
			if (last_visited_node->get_children_count() == 0 && !_is_right_child(last_visited_node))
			{
				return last_visited_node->get_parent();
			}
			else if (last_visited_node->has_right_child())
			{
				node_ptr right_child = last_visited_node->get_right_child();
				if (!right_child->has_left_child())
					return right_child;
				return _get_left_most_child(right_child);
			}
			else if (last_visited_node->get_children_count() <= 1 && _is_right_child(last_visited_node))
			{
				node_ptr current_node = last_visited_node->get_parent();
				while (current_node && current_node->get_key() < last_visited_node->get_key())
				{
					current_node = current_node->get_parent();
				}
				return current_node;
			}
			else if (!last_visited_node->has_right_child())
				return last_visited_node->get_parent();
			return last_visited_node->get_parent()->get_parent();

		}

		/* Inserter Functions */
	public:
		inline void insert(const value_type &key)
		{
			this->reset_traversal();

			if (this->_root == NULL)
			{
				this->_root = _new_node(NULL, key);
				this->_root->set_color(node_type::BLACK);
				return;
			}

			node_ptr new_node = NULL;

			{
				node_ptr place_to_insert_new_node = this->_get_place_to_insert_new_node(key);

				new_node = this->_new_node(place_to_insert_new_node, key, node_type::RED);
				if (key < place_to_insert_new_node->get_key())
					place_to_insert_new_node->set_left_child(new_node);
				else if (key > place_to_insert_new_node->get_key())
					place_to_insert_new_node->set_right_child(new_node);
				else
				{
					// Node is already in Tree
				}
			}

			if (!_node_is_roots_child(new_node))
				this->_fix_tree(new_node);
		}

	private:
		void _iterate_fix_tree(node_ptr node)
		{
			node_ptr current = node;

			if (current == NULL)
				return;

			if (current->get_left_child() != NULL)
			{
				this->_iterate_fix_tree(current->get_left_child());
			}
			if (current->get_right_child() != NULL)
			{
				this->_iterate_fix_tree(current->get_right_child());
			}
			this->_fix_tree(current);
		}

		/**
		 * @brief Checks if the current Node Violates any Property and fixes them
		 * @param node to check
		 */
		void _fix_tree(node_ptr &node)
		{
			// Cases from: https://www.happycoders.eu/algorithms/red-black-tree-java/#red-black-tree-insertion <- this is good :)


			// Case 1: New Node is Root (RBT is Empty)
			if (node == this->_root)
				return;

			node_ptr parent = node->get_parent();
			if (parent->is_black())
				return;

			node_ptr grand_parent = parent->get_parent();
			if (grand_parent == NULL)
			{
				parent->set_color(node_type::BLACK);
				return;
			}

			node_ptr aunt = node->get_aunt();

			if (aunt != NULL && aunt->get_color() == node_type::RED)
			{
				parent->set_color(node_type::BLACK);
				grand_parent->set_color(node_type::RED);
				aunt->set_color(node_type::BLACK);

				_fix_tree(grand_parent);
				return;
			}

			if (parent == grand_parent->get_left_child())
			{
				if (node == parent->get_right_child())
				{
					this->_left_rotation(parent);
					parent = node;
				}

				this->_right_rotation(grand_parent);

				parent->set_color(node_type::BLACK);
				grand_parent->set_color(node_type::RED);
				return;
			}

			if (node == parent->get_left_child())
			{
				this->_right_rotation(parent);
				parent = node;
			}

			this->_left_rotation(grand_parent);

			parent->set_color(node_type::BLACK);
			grand_parent->set_color(node_type::RED);
		}

		inline bool _node_is_roots_child(node_ptr node)
		{
			if (node->get_parent() == NULL)
				return false;
			return node->get_parent()->get_parent() == NULL;
		}

		/**
		 * @brief Returns a suitable place to insert data
		 * @param key Data to Inserter
		 * @return A suitable place for insertion
		 */
		inline node_ptr _get_place_to_insert_new_node(const value_type &key) const
		{
			node_ptr place_to_insert_new_node = NULL;

			for (node_ptr current_node = this->_root; current_node != NULL;)
			{
				place_to_insert_new_node = current_node;
				current_node = this->_iterate_tree_by_key(current_node, key);
			}

			return place_to_insert_new_node;
		}

		/**
		 * @brief Iterates the Red Black Tree (based on comparison of keys)
		 * @param current_node
		 * @param key
		 * @return
		 */
		inline node_ptr _iterate_tree_by_key(const node_ptr &current_node, value_type key) const
		{
			if (current_node == NULL)
				return NULL;

			if (key < current_node->get_key())
			{
				return current_node->get_left_child();
			}
			return current_node->get_right_child();
		}

		/* Erasure Functions */
	public:
		inline void erase(const value_type &key)
		{
			this->reset_traversal();

			node_ptr key_to_erase = this->_get_node_to_erase(key);
			if (key_to_erase == NULL)
				return;

			this->_erase_key(key_to_erase);
		}

	private:
		inline bool _erase_key(node_ptr &key_to_erase)
		{
			if (key_to_erase == NULL)
				return false;

			node_ptr moved_up_node;
			typename node_type::node_color erased_node_color;

			int to_erase_children_count = key_to_erase->get_children_count();

			if (to_erase_children_count == 0 || to_erase_children_count == 1)
			{
				moved_up_node = this->_delete_node_zero_or_one_child(key_to_erase);
				erased_node_color = key_to_erase->get_color();

				node_type::delete_node(key_to_erase);
			}
			else
			{
				node_ptr in_order_successor = this->_find_minimum(key_to_erase->get_right_child());

				key_to_erase->set_key(in_order_successor->get_key());

				moved_up_node = this->_delete_node_zero_or_one_child(in_order_successor);
				erased_node_color = in_order_successor->get_color();

				node_type::delete_node(in_order_successor);
			}

			if (erased_node_color == node_type::BLACK)
			{
				this->_fix_tree(moved_up_node);
				if (this->_is_nil_node(moved_up_node))
				{
					this->_replace_parents_child(moved_up_node->get_parent(), moved_up_node, NULL);
					node_type::delete_node(moved_up_node);
				}
			}

			return true;
		}

		node_ptr _get_node_to_erase(const value_type &key)
		{
			node_ptr current = this->_root;

			while (current != NULL)
			{
				if (key == current->get_key())
					break;

				if (key < current->get_key())
					current = current->get_left_child();
				else
					current = current->get_right_child();
			}

			if (key != current->get_key())
				return NULL;
			return current;
		}

		node_ptr _find_minimum(node_ptr node)
		{
			while (node->get_left_child() != NULL)
				node = node->get_left_child();
			return node;
		}

		void _replace_parents_child(node_ptr parent, node_ptr old_child, node_ptr new_child)
		{
			if (parent == NULL)
				this->_root = new_child;
			else if (parent->get_left_child() == old_child)
			{
				if (new_child == NULL)
					parent->reset_left_child();
				else
					parent->set_left_child(new_child);
			}
			else if (parent->get_right_child() == old_child)
			{
				if (new_child == NULL)
					parent->reset_right_child();
				else
					parent->set_right_child(new_child);
			}
			if (new_child != NULL)
				new_child->set_parent(parent);
		}

		node_ptr _delete_node_zero_or_one_child(node_ptr to_erase)
		{
			if (to_erase->has_left_child())
			{
				this->_replace_parents_child(to_erase->get_parent(), to_erase, to_erase->get_left_child());
				return to_erase->get_left_child();
			}
			else if (to_erase->has_right_child())
			{
				this->_replace_parents_child(to_erase->get_parent(), to_erase, to_erase->get_right_child());
				return to_erase->get_right_child();
			}
			else
			{
				node_ptr new_child =
						to_erase->get_color() == node_type::BLACK ? this->_new_nil_node() : NULL;
				this->_replace_parents_child(to_erase->get_parent(), to_erase, new_child);
				return new_child;
			}
		}

		void _erase_fix_tree(node_ptr node)
		{
			if (node == NULL)
				return;

			if (node == this->_root)
			{
				node->set_color(node_type::BLACK);
				return;
			}

			node_ptr sibling = node->get_sibling();

			if (sibling->is_red())
			{
				sibling->set_color(node_type::BLACK);
				node->get_parent()->set_color(node_type::RED);

				if (node == node->get_parent()->get_left_child())
					this->_left_rotation(node->get_parent());
				else
					this->_right_rotation(node->get_parent());
			}

			if (sibling->get_left_child()->is_black() && sibling->get_right_child()->is_black())
			{
				sibling->set_color(node_type::RED);

				if (node->get_parent()->is_red())
					node->get_parent()->set_color(node_type::BLACK);
				else
					this->_erase_fix_tree(node->get_parent());
			}
			else
			{
				bool node_is_left_child = node == node->get_parent()->get_left_child();

				if (node_is_left_child && sibling->get_right_child()->is_black())
				{
					sibling->get_left_child()->set_color(node_type::BLACK);
					sibling->set_color(node_type::RED);
					this->_right_rotation(sibling);
					sibling = node->get_parent()->get_right_child();
				}
				else if (!node_is_left_child && sibling->get_left_child()->is_black())
				{
					sibling->get_right_child()->set_color(node_type::BLACK);
					sibling->set_color(node_type::RED);
					this->_left_rotation(sibling);
					sibling = node->get_parent()->get_left_child();
				}

				sibling->set_color(node->get_parent()->get_color());
				node->get_parent()->set_color(node_type::BLACK);
				if (node_is_left_child)
				{
					sibling->get_right_child()->set_color(node_type::BLACK);
					this->_left_rotation(node->get_parent());
				}
				else
				{
					sibling->get_left_child()->set_color(node_type::BLACK);
					this->_right_rotation(node->get_parent());
				}
			}
		}

	public:
		inline void clear()
		{
			while (this->_root)
			{
				this->erase(this->_root->get_key());
			}
		}

		/* Private Member Functions */
	private:
		bool _is_nil_node(const node_ptr node) const
		{
			node_ptr res = dynamic_cast<nil_node_type *>(node);
			if (res != NULL)
			{
//				std::cout << "node is nil node" << std::endl;
				return true;
			}
			return false;
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
