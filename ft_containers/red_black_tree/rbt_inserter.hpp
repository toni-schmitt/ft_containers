#pragma once

#include <memory>

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
	class rbt_inserter
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

		/* Private Local Class */
	private:
		class rbt_insertion_fixer
		{

			friend class rbt_inserter;

			/* Member Types */
		private:
			typedef rbt_inserter<value_type, allocator_type> caller_type;

			/* Private Members */
		private:
			caller_type &_caller_class;

			/* Constructor */
		public:
			explicit rbt_insertion_fixer(caller_type &caller_class = caller_type()) : _caller_class(
					caller_class)
			{
			}

		private:
			rbt_insertion_fixer &operator=(const rbt_insertion_fixer &copy)
			{
				( void ) copy;
				throw not_allowed_constructor_call();
			}

			struct not_allowed_constructor_call : public std::exception
			{
				const char *what() const throw()
				{
					return "Pls dont call this :(";
				}
			};

			/* Private Member Functions */
		private:
			void _fix_left_lean(node_ptr &node)
			{
				// case 3.2.3

				node_ptr parent = node->get_parent();
				node_ptr grand_parent = parent->get_parent();

				// TODO: Reimplement Rotation Function
				this->_caller_class._caller_class._right_rotation(grand_parent);
				grand_parent->set_color(node_type::RED);
				parent->set_color(node_type::BLACK);
			}

			bool _is_left_leaning(const node_ptr &node)
			{
				if (node == NULL)
					return false;

				const node_ptr parent = node->get_parent();
				const node_ptr grand_parent = parent->get_parent();

				// If node is not left of parent and parent is not left of grand_parent
				if (node != parent->get_left_child() && parent != grand_parent->get_left_child())
					// Tree cannot be left leaning since Parent and Grandparent are not on left side
					return false;

				// If grand_parent is not black
				if (!grand_parent->is_black())
					// Tree does not need fixing, since Red Grandparent is valid
					return false;

				// If parent and node are not red
				if (!parent->is_red() && !node->is_red())
					// Tree does not need fixing, since two consecutive blacks are allowed
					return false;

				return true;
			}

			bool _is_red_triangle(const node_ptr &node)
			{
				if (node == NULL)
					return false;

				const node_ptr parent = node->get_parent();
				const node_ptr grand_parent = parent->get_parent();
				const node_ptr aunt = node->get_aunt();

				if (parent == NULL || grand_parent == NULL || aunt == NULL)
					return false;

				if (!node->is_red())
					// Tree cannot have red triangle because one of 3 nodes is not red
					return false;

				if (!parent->is_red())
					// Tree cannot have red triangle because one of 3 nodes is not red
					return false;

				if (!aunt->is_red())
					// Tree cannot have red triangle because one of 3 nodes is not red
					return false;

				return true;
			}

			void _fix_red_triangle(node_ptr &node)
			{
				node_ptr parent = node->get_parent();
				node_ptr grand_parent = node->get_parent();
				node_ptr aunt = node->get_aunt();

				// Only recolor Grandparent if it is not the Root Node
				if (grand_parent != this->_caller_class._caller_class._root)
					grand_parent->set_color(node_type::RED);
				parent->set_color(node_type::BLACK);
				aunt->set_color(node_type::BLACK);
			}

			bool _is_right_leaning(const node_ptr &node)
			{
				if (node == NULL)
					return false;

				const node_ptr parent = node->get_parent();
				const node_ptr grand_parent = parent->get_parent();

				// If Node is not on right side of parent
				if (node != parent->get_right_child())
					return false;

				// If Parent is not on right side of grandparent
				if (parent != grand_parent->get_right_child())
					return false;

				return true;
			}

			void _fix_right_lean(node_ptr &node)
			{
				node_ptr parent = node->get_parent();
				node_ptr grand_parent = parent->get_parent();

				this->_caller_class._caller_class._left_rotation(node);
				grand_parent->set_color(node_type::RED);
				parent->set_color(node_type::BLACK);
			}

			inline bool _is_right_left_leaning(node_ptr &node)
			{
				if (node == NULL)
					return false;

				const node_ptr parent = node->get_parent();
				const node_ptr grand_parent = parent->get_parent();

				// If Node is not on left side of parent
				if (node != parent->get_left_child())
					return false;

				// If Parent is not on right side of grandparent
				if (parent != grand_parent->get_right_child())
					return false;

				return true;
			}

			void _fix_right_left_lean(node_ptr &node)
			{
				node_ptr parent = node->get_parent();

				this->_caller_class._caller_class._right_rotation(parent);
				_fix_right_lean(node);
			}

			inline bool _is_left_right_leaning(node_ptr &node)
			{
				if (node == NULL)
					return false;

				const node_ptr parent = node->get_parent();
				const node_ptr grand_parent = parent->get_parent();

				// If Node is not on left side of parent
				if (node != parent->get_right_child())
					return false;

				// If Parent is not on right side of grandparent
				if (parent != grand_parent->get_left_child())
					return false;

				return true;
			}

			void _fix_left_right_lean(node_ptr &node)
			{
				node_ptr parent = node->get_parent();

				this->_caller_class._caller_class._left_rotation(parent);
				_fix_left_lean(node);
			}

			/* Public Member Functions */
		public:
			/**
			 * @brief Checks if the current Node Violates any Property and fixes them
			 * @param node to check
			 */
			void fix_tree(node_ptr &node)
			{
				// Cases from: https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/#Insertion
				// case 1 (rbt is Empty, not handled here)

				// case 2 (Parent of node is black)
				// does not violate any property

				// case 3 (Parent of node is red)
				// This violates Property 4
				// If a Node is Red, both of its children are black
				if (!node->is_red() || !node->get_parent()->is_red())
					return;
				/// CASE 3.x

				// case 3.1
				if (_is_red_triangle(node))
				{
					_fix_red_triangle(node);
					return;
				}

				// We need to check the Aunt of node to see if the Tree is further violated
				/// CASE 3.2.x
				const node_ptr aunt = node->get_aunt();
				if (aunt != NULL && !aunt->is_black())
					return;
				// case 3.2.1
				if (_is_right_leaning(node))
					_fix_right_lean(node);

				// case 3.2.2
				if (_is_right_left_leaning(node))
					_fix_right_left_lean(node);

				// case 3.2.3
				if (_is_left_leaning(node))
					_fix_left_lean(node);

				// case 3.2.3
				if (_is_left_right_leaning(node))
					_fix_left_right_lean(node);

			}

		};

		/* Private Members */
	private:
		caller_type &_caller_class;
		rbt_insertion_fixer _insertion_fixer;

		/* Constructor */
	public:
		rbt_inserter()
		{
			this->_insertion_fixer = rbt_insertion_fixer(*this);
		}

		explicit rbt_inserter(caller_type &caller_class) : _caller_class(caller_class),
														   _insertion_fixer(rbt_insertion_fixer(*this))
		{
		}

		/* Public Member Functions */
	public:
		void insert(const value_type &data)
		{
			node_ptr new_node = NULL;

			{
				node_ptr place_to_insert_new_node = this->_get_place_to_insert_new_node(data);

				new_node = new node_type(place_to_insert_new_node, data, node_type::RED);
				if (data < place_to_insert_new_node->get_data())
					place_to_insert_new_node->set_left_child(new_node);
				else
					place_to_insert_new_node->set_right_child(new_node);
			}

			if (new_node->get_parent()->get_parent() == NULL)
				return;

			this->_insertion_fixer.fix_tree(new_node);
		}

		/* Private Member Functions */
	private:
		/**
			 * @brief Returns a suitable place to insert data
			 * @param data Data to Inserter
			 * @return A suitable place for insertion
			 */
		inline node_ptr _get_place_to_insert_new_node(const value_type &data) const
		{
			node_ptr place_to_insert_new_node = NULL;

			for (node_ptr current_node = this->_caller_class._root; current_node != NULL;)
			{
				place_to_insert_new_node = current_node;
				current_node = this->_iterate_tree_by_data(current_node, data);
			}

			return place_to_insert_new_node;
		}

		/**
		 * @brief Iterates the Red Black Tree (based on comparison of keys)
		 * @param current_node
		 * @param data
		 * @return
		 */
		inline node_ptr _iterate_tree_by_data(const node_ptr &current_node, value_type data) const
		{
			if (current_node == NULL)
				return NULL;

			if (data < current_node->get_data())
			{
				return current_node->get_left_child();
			}
			return current_node->get_right_child();
		}
	};

} // namespace ft