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
				this->fix_tree(current);
			}

			/* Public Member Functions */
		public:
			/**
			 * @brief Checks if the current Node Violates any Property and fixes them
			 * @param node to check
			 */
			void fix_tree(node_ptr &node)
			{
				// Cases from: https://www.happycoders.eu/algorithms/red-black-tree-java/#red-black-tree-insertion <- this is good :)


				// Case 1: New Node is Root (RBT is Empty)
				if (node == this->_caller_class._caller_class._root)
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

					fix_tree(grand_parent);
					return;
				}

				if (parent == grand_parent->get_left_child())
				{
					if (node == parent->get_right_child())
					{
						this->_caller_class._caller_class._left_rotation(parent);
						parent = node;
					}

					this->_caller_class._caller_class._right_rotation(grand_parent);

					parent->set_color(node_type::BLACK);
					grand_parent->set_color(node_type::RED);
					return;
				}

				if (node == parent->get_left_child())
				{
					this->_caller_class._caller_class._right_rotation(parent);
					parent = node;
				}

				this->_caller_class._caller_class._left_rotation(grand_parent);

				parent->set_color(node_type::BLACK);
				grand_parent->set_color(node_type::RED);
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
		/**
		 * Inserts the key into the RB-Tree
		 * @param key Key to Insert
		 * @return true on success, false on failure
		 */
		bool insert(const value_type &key)
		{
			node_ptr new_node = NULL;

			{
				node_ptr place_to_insert_new_node = this->_get_place_to_insert_new_node(key);

				new_node = this->_caller_class._new_node(place_to_insert_new_node, key, node_type::RED);
				if (key < place_to_insert_new_node->get_key())
					place_to_insert_new_node->set_left_child(new_node);
				else if (key > place_to_insert_new_node->get_key())
					place_to_insert_new_node->set_right_child(new_node);
				else
				{
					// Node is already in Tree
					return false;
				}
			}

			if (!_node_is_roots_child(new_node))
				this->_insertion_fixer.fix_tree(new_node);
			return true;
		}

		/* Private Member Functions */
	private:
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

			for (node_ptr current_node = this->_caller_class._root; current_node != NULL;)
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
	};

} // namespace ft