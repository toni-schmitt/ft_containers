#pragma once

#include <memory>
#include <typeinfo>

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
	class rbt_eraser
	{
		friend class ft::red_black_tree<T, Alloc>;

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
		typedef typename caller_type::nil_node_type nil_node_type;

		/* Private Members */
	private:
		caller_type &_caller_class;

		/* Constructor */
	public:
		explicit rbt_eraser(caller_type &caller_class) : _caller_class(caller_class) { }

		/* Private Member Functions */
	private:
		node_ptr _get_node_to_erase(const value_type &key)
		{
			node_ptr current = this->_caller_class._root;

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
				this->_caller_class._root = new_child;
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
						to_erase->get_color() == node_type::BLACK ? this->_caller_class._new_nil_node() : NULL;
				this->_replace_parents_child(to_erase->get_parent(), to_erase, new_child);
				return new_child;
			}
		}

		void _fix_tree(node_ptr node)
		{
			if (node == NULL)
				return;

			if (node == this->_caller_class._root)
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
					this->_caller_class._left_rotation(node->get_parent());
				else
					this->_caller_class._right_rotation(node->get_parent());
			}

			if (sibling->get_left_child()->is_black() && sibling->get_right_child()->is_black())
			{
				sibling->set_color(node_type::RED);

				if (node->get_parent()->is_red())
					node->get_parent()->set_color(node_type::BLACK);
				else
					this->_fix_tree(node->get_parent());
			}
			else
			{
				bool node_is_left_child = node == node->get_parent()->get_left_child();

				if (node_is_left_child && sibling->get_right_child()->is_black())
				{
					sibling->get_left_child()->set_color(node_type::BLACK);
					sibling->set_color(node_type::RED);
					this->_caller_class._right_rotation(sibling);
					sibling = node->get_parent()->get_right_child();
				}
				else if (!node_is_left_child && sibling->get_left_child()->is_black())
				{
					sibling->get_right_child()->set_color(node_type::BLACK);
					sibling->set_color(node_type::RED);
					this->_caller_class._left_rotation(sibling);
					sibling = node->get_parent()->get_left_child();
				}

				sibling->set_color(node->get_parent()->get_color());
				node->get_parent()->set_color(node_type::BLACK);
				if (node_is_left_child)
				{
					sibling->get_right_child()->set_color(node_type::BLACK);
					this->_caller_class._left_rotation(node->get_parent());
				}
				else
				{
					sibling->get_left_child()->set_color(node_type::BLACK);
					this->_caller_class._right_rotation(node->get_parent());
				}
			}
		}
		/* Public Member Functions */
	public:
		bool erase(const node_ptr &to_erase)
		{
			if (to_erase == NULL)
				return false;

			node_ptr moved_up_node;
			typename node_type::node_color erased_node_color;

			int to_erase_children_count = to_erase->get_children_count();

			if (to_erase_children_count == 0 || to_erase_children_count == 1)
			{
				moved_up_node = this->_delete_node_zero_or_one_child(to_erase);
				erased_node_color = to_erase->get_color();
			}
			else
			{
				node_ptr in_order_successor = this->_find_minimum(to_erase->get_right_child());

				to_erase->set_key(in_order_successor->get_key());

				moved_up_node = this->_delete_node_zero_or_one_child(in_order_successor);
				erased_node_color = in_order_successor->get_color();
			}

			if (erased_node_color == node_type::BLACK)
			{
				this->_fix_tree(moved_up_node);
				if (typeid(moved_up_node) == typeid(nil_node_type))
				{
					this->_replace_parents_child(moved_up_node->get_parent(), moved_up_node, NULL);
				}
			}

			return true;
		}

		bool erase(const value_type &key)
		{
			node_ptr to_erase = _get_node_to_erase(key);
			if (to_erase == NULL)
				return false;

			return this->erase(to_erase);
		}

	private:
	};
} // namespace ft