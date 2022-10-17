#pragma once

#include <memory>
#include <list>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class rbt_traverser
	{
		friend class red_black_tree<T, Alloc>;

		/* Member Types */
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

	private:
		typedef ft::red_black_tree<value_type, allocator_type> caller_type;
		typedef typename caller_type::node_type node_type;
		typedef typename node_type::node_ref node_ref;
		typedef typename node_type::const_node_ref const_node_ref;
		typedef typename node_type::node_ptr node_ptr;
		typedef typename node_type::const_node_ptr const_node_ptr;
		typedef typename node_type::node_color node_color;

		/* Private Members */
	private:
		caller_type &_red_black_tree;
		node_ptr &_root;

		/* Constructor */
	public:
		rbt_traverser() { }

		explicit rbt_traverser(caller_type &caller_class) : _red_black_tree(caller_class), _root(caller_class._root) { }

		/* Public Member Functions */
		node_ptr get_last_visited_node() const
		{
			return _last_visited_node();
		}

		void reset_traversal() const
		{
			_last_visited_node(NULL, true);
		}

		node_ptr get_next_node(bool reset = false) const
		{

			if (reset)
				this->reset_traversal();

			node_ptr next_node = _get_next_node(_last_visited_node());
			if (this->_red_black_tree._is_nil_node(next_node))
				return NULL; // TODO: Better thing to return here
			_last_visited_node(next_node);
			return next_node;
		}

		node_ptr get_last_node(bool reset = false) const
		{
			if (reset)
				this->reset_traversal();

			if (_last_visited_node() == NULL)
				return NULL; // TODO: Better thing to return here
			node_ptr last_node = _get_last_node(_last_visited_node());
			if (this->_red_black_tree._is_nil_node(last_node))
				return NULL; // TODO: Better thing to return here
			_last_visited_node(last_node);
			return last_node;
		}


		/* Private Member Functions */
	private:
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

	};
} // namespace ft
