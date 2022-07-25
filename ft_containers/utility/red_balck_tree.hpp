#pragma once

#include <memory>
#include <cstdlib>

typedef unsigned int uint;

namespace ft
{

	/**
	 * @brief Node Structure for Red Black Tree
	 *
	 * @tparam T Value Type of Node Data
	 * @tparam Alloc Allocator of Value Type (Defaults to std::allocator<T>)
	 */
	template < class T, class Alloc = std::allocator<T> >
	struct rbt_node
	{
		/* Member Types */
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference value_ref;
		typedef typename allocator_type::const_reference value_const_ref;
		typedef typename allocator_type::pointer value_ptr;
		typedef typename allocator_type::const_pointer value_const_ptr;
		typedef rbt_node &node_ref;
		typedef const rbt_node &const_node_ref;
		typedef rbt_node *node_ptr;
		typedef const rbt_node *const_node_ptr;

	public:
		enum node_color
		{
			red = 0,
			black = 1
		};

		/* Private Members */
	private:
		node_ptr _parent;
		value_type _data;
		node_color _color;
		node_ptr _left_child;
		node_ptr _right_child;

		/* Constructors */
	public:
		/**
		 * @brief Construct a new rbt node object
		 *
		 * @param parent Parent of the node
		 * @param data Data of the node
		 * @param color Color of the node
		 * @param left_child Left Child of the node
		 * @param right_child Right Child of the node
		 */
		rbt_node(
				node_ptr parent, value_type data, node_color color = black, node_ptr left_child = NULL,
				node_ptr right_child = NULL
		)
		{
			this->_parent = parent;
			this->_data = data;
			this->_color = color;
			this->_left_child = left_child;
			this->_right_child = right_child;
		}

		/* Destructors */
	public:
		~rbt_node() { }

		/* Static Functions */
	public:
		static inline node_ptr get_parent(node_ptr node)
		{
			if (node == NULL)
				return node_ptr();

			return node->get_parent();
		}

		static inline value_type get_data(node_ptr node)
		{
			if (node == NULL)
				return value_type();

			return node->get_data();
		}

		static inline node_color get_color(node_ptr node)
		{
			if (node == NULL)
				return node_color();

			return node->get_color();
		}

		static inline node_ptr get_left_child(node_ptr node)
		{
			if (node == NULL)
				return node_ptr();

			return node->get_left_child();
		}

		static inline node_ptr get_right_child(node_ptr node)
		{
			if (node == NULL)
				return node_ptr();

			return node->get_right_child();
		}

		/* Modifiers functions */
	public:
		static inline void flip_color(node_ptr node)
		{
			if (node == NULL)
				return;

			node->flip_color();
		}

		inline void flip_color()
		{
			if (this->_color == black)
				this->_color = red;
			else if (this->_color == red)
				this->_color = black;
		}

	public:
		/* Getter */
		inline node_ptr get_parent() { return this->_parent; }

		inline value_type get_data() { return this->_data; }

		inline value_type get_color() { return this->_color; }

		inline node_ptr get_left_child() { return this->_left_child; }

		inline node_ptr get_right_child() { return this->_right_child; }

		/* Setter */
	public:
		inline void set_left_child(node_ptr left_child)
		{
			if (left_child == NULL)
				return;

			this->_left_child = left_child;
		}

		inline void set_right_child(node_ptr right_child)
		{
			if (right_child == NULL)
				return;

			this->_right_child = right_child;
		}

		inline void set_parent(node_ptr parent)
		{
			if (parent == NULL)
				return;

			this->_parent = parent;
		}

		inline void set_color(node_color color) { this->_color = color; }


		/* Special Modifier functions */
	public:
		static inline void reset_left_child(node_ptr node)
		{
			if (node == NULL)
				return;

			node->reset_left_child();
		}

		inline void reset_left_child() { this->_left_child = NULL; }

		static inline void reset_right_child(node_ptr node)
		{
			if (node == NULL)
				return;

			node->reset_right_child();
		}

		inline void reset_right_child() { this->_right_child = NULL; }
	};

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

	private:
		typedef rbt_node<value_type, allocator_type> node_type;
		typedef typename node_type::node_ref node_ref;
		typedef typename node_type::const_node_ref const_node_ref;
		typedef typename node_type::node_ptr node_ptr;
		typedef typename node_type::const_node_ptr const_node_ptr;
		typedef typename node_type::node_color node_color;
		typedef enum { left_rotation = 0, right_rotation = 1 } rotate_direction;

		/* Private Local Class */
	private:
		/**
		 * @brief Local Class for Insertion into the Red Black Tree
		 */
		class Inserter
		{
			/* Private Locals Insertion Fixer Class */
		private:
			class InsertionFixer
			{
			private:
				const Inserter &_parent_class;

			private:
				void _fix_case_3(node_ptr &new_node, node_ptr uncle)
				{
					if (uncle->get_color() == node_type::red)
					{
						uncle->set_color(node_type::black);
						new_node->get_parent()->set_color(node_type::black);
						new_node->get_parent()->get_parent()->set_color(node_type::red);
						new_node = new_node->get_parent()->get_parent();
					}
					else
					{
						if (new_node == new_node->get_parent()->get_left_child())
						{
							new_node = new_node->get_parent();
							this->_parent_class._parent_class._rotate(new_node, right_rotation);
						}
						new_node->get_parent()->set_color(node_type::black);
						new_node->get_parent()->get_parent()->set_color(node_type::red);
						this->_parent_class._parent_class._rotate(new_node, left_rotation);
					}
				}

			public:
				explicit InsertionFixer(const Inserter &parent_class) : _parent_class(parent_class) { }

				void fix(node_ptr &new_node)
				{
					node_ptr uncle;

					while (new_node->get_parent()->get_color() == node_type::red)
					{
						if (new_node->get_parent() == new_node->get_parent()->get_parent()->get_right_child())
						{
							uncle = new_node->get_parent()->get_left_child();
							this->_fix_case_3(new_node, uncle);
						}
						else
						{
							uncle = new_node->get_parent()->get_parent()->get_right_child();
							this->_fix_case_3(new_node, uncle);
						}
						if (new_node == this->_parent_class._parent_class._root)
						{
							break;
						}
					}
					this->_parent_class._parent_class._root->set_color(node_type::black);
				}
			};

		private:
			/* Parent Class of Local Class for Insertion */
			const red_black_tree<T, Alloc> &_parent_class;
			const InsertionFixer &_insertion_fixer;

		public:
			/**
			 * @brief Parameter Constructor
			 * @param parent_class Reference to Class that called Constructor
			 */
			explicit Inserter(const red_black_tree<T, Alloc> &parent_class) : _parent_class(parent_class)
			{
				this->_insertion_fixer = InsertionFixer(*this);
			}

			/**
			 * @brief Inserts data into the Red Black Tree
			 * @param data
			 */
			inline void insert(const value_type &data) const
			{
				node_ptr new_node;

				{
					node_ptr place_to_insert_new_node = this->_get_place_to_insert_new_node(data);

					new_node = new node_type(place_to_insert_new_node, data, node_type::red);
					if (data < place_to_insert_new_node->get_data())
						place_to_insert_new_node->set_left_child(new_node);
					else
						place_to_insert_new_node->set_right_child(new_node);
				}

				if (new_node->get_parent()->get_parent() == NULL)
					return;

				this->_insertion_fixer.fix(new_node);
			}

			/**
			 * @brief Returns a suitable place to insert data
			 * @param data Data to Inserter
			 * @return A suitable place for insertion
			 */
			inline node_ptr _get_place_to_insert_new_node(const value_type &data) const
			{
				node_ptr place_to_insert_new_node = NULL;

				for (node_ptr current_node = this->_parent_class._root; current_node != NULL;)
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
			inline node_ptr _iterate_tree_by_data(node_ptr &current_node, value_type data) const
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

		/* Private Members */
	private:
		node_ptr _root;
		const Inserter _inserter;



		/* Constructors */
	public:
		/**
		 * @brief Construct a new red black tree object
		 */
		red_black_tree() : _inserter(Inserter(*this))
		{
			this->_root = NULL;
		}

		explicit red_black_tree(const value_type &data) : _inserter(Inserter(*this))
		{
			this->insert(data);
		}
		/* Modifiers functions */
	public:
		/**
		 * @brief Insert data into the Red Black Tree
		 *
		 * @param data The Data to insert
		 */
		inline void insert(value_type data)
		{
		}

		/**
		 * @brief Erases data from the Red Black Tree
		 * @param data The Data to erase
		 */
		inline void erase(value_type data)
		{
		}
	};
} // namespace ft
