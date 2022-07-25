#pragma once

#include <memory>
#include <cstdlib>

typedef unsigned int uint;

namespace ft
{

	/**
	 * @brief Node Structor for Red Black Tree
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

		/* Protected Members */
	protected:
		node_ptr parent;
		value_type data;
		node_color color;
		node_ptr left_child;
		node_ptr right_child;

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
				node_ptr parent, value_type data, node_color color = node_color::black, node_ptr left_child = NULL,
				node_ptr right_child = NULL
		)
		{
			this->parent = parent;
			this->_data = data;
			this->_color = color;
			this->left_child = left_child;
			this->right_child = right_child;
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
		/* Getter */
		inline node_ptr get_parent() { return this->parent; }

		inline value_type get_data() { return this->data; }

		inline value_type get_color() { return this->color; }

		inline node_ptr get_left_child() { return this->left_child; }

		inline node_ptr get_right_child() { return this->right_child; }

		/* Setter */
	public:
	};

	// search, insert, delete (main operations)
	// helpers: rotation, color flip
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

		/* Private Members */
	private:
		node_ptr _root;

		/* Private Functions */
	private:
		/**
		 * @brief Flips color of node
		 *
		 * @param node Node of which to flip color
		 */
		inline void _color_flip(node_ptr node)
		{
			node->flip_color();
		}

		/**
		 * @brief Rotate node in direction
		 *
		 * @details Based on direction (either left or right) the rotation a node makes the node go down in direction and as a result, the child at direction (left or right) goes up.
		 * @param direction Either left (true) or right (false)
		 * @return node_ptr
		 */
		inline node_ptr _rotate(node_ptr node, bool direction)
		{

			node_ptr tmp = node->get_children()[!direction];
			//node->set_child(!direction, tmp->get_children()[direction]);
			node->get_children()[!direction] = tmp
					->get_children()[direction]; // Opposite child = Opposite childs direction (left/right) child
			//tmp->set_child(direction, node);
			tmp->get_children()[direction] = node;

			node_type::set_color(tmp, node->get_color());
			node_type::set_color(node, node_type::red);

			return tmp;
		}

		inline node_ptr _double_rotate(node_ptr node, bool direction)
		{
			node->get_children()[direction] = _rotate(node->get_children()[!direction], !direction);
			return _rotate(node, direction);
		}

		node_ptr _insert_fix(node_ptr node, bool direction)
		{
			node_ptr *node_children = node->get_children();

			if (node_type::is_red(node_children[direction]))
			{
				if (node_type::is_red(node_children[!direction]))
				{
					if (node_type::is_red(node_children[direction]->get_children()[direction]) ||
					    node_type::is_red(node_children[direction]->get_children()[!direction]))
					{
						node->flip_color();
					}
				}
				else
				{
					if (node_type::is_red(node_children[direction]->get_children()[direction]))
					{
						node = _rotate(node, !direction);
					}
					else if (node_type::is_red(node_children[direction]->get_children()[!direction]))
					{
						node = _double_rotate(node, !direction);
					}
				}
			}

			return node;
		}

		inline node_ptr _insert(node_ptr node, value_type data)
		{
			if (node == NULL)
				return new node_type(data, node_type::red);

			bool direction = data > node->get_data();

			node->get_children()[direction] = _insert(node->get_children()[direction], data);

			return _insert_fix(node, direction);
		}


		// Assumes that node only has one or fewer children
		inline node_ptr get_available_child(node_ptr node)
		{
			if (node->has_left_child())
				return node->get_left_child();
			if (node->has_right_child())
				return node->get_right_child();
			return NULL;
		}

		node_ptr _erase_key(node_ptr key, bool &tree_is_balanced, value_type &data)
		{
			if (key->get_children_count() <= 1)
			{
				node_ptr available_child = get_available_child(key);

				if (key->is_red())
				{
					delete key;
					tree_is_balanced = true;
				}
				else if (node_type::is_red(available_child))
				{
					node_type::set_color(available_child, node_type::black);
					delete key;
					tree_is_balanced = true;
				}

				return available_child;
			}

			if (key->get_children_count() == 2)
			{
				node_ptr tmp = key->get_left_child()->get_max();

				key->set_data(tmp->get_data());
				data = tmp->get_data();
				return NULL;
			}
			return NULL;
		}

		node_ptr _erase_fix(node_ptr node, bool direction, bool &tree_is_balanced)
		{
			node_ptr parent = node;
			node_ptr sibling = node->get_children()[!direction];

			if (node_type::is_red(sibling))
			{
				node = _rotate(node, direction);
				sibling = parent->get_children()[!direction];
			}

			if (sibling == NULL)
				return node;

			if (node_type::is_red(sibling->get_left_child()) == false
			&& node_type::is_red(sibling->get_right_child()) == false)
			{
				if (parent->is_red())
					tree_is_balanced = true;

				node_type::set_color(parent, node_type::black);
				node_type::set_color(sibling, node_type::red);
				return node;
			}

			node_color initial_color_parent = parent->get_color();
			bool is_red_sibling_reduction = !(node == parent);

			if (node_type::is_red(sibling->get_children()[!direction]))
			{
				parent = _rotate(parent, direction);
			}
			else
			{
				parent = _double_rotate(parent, direction);
			}

			node_type::set_color(parent, initial_color_parent);
			node_type::set_color(parent->get_left_child(), node_type::black);
			node_type::set_color(parent->get_right_child(), node_type::black);

			if (is_red_sibling_reduction)
			{
				node->get_children()[direction] = parent;
			}
			else
			{
				node = parent;
			}

			tree_is_balanced = true;

			return node;

		}

		inline node_ptr _erase(node_ptr node, value_type data, bool &tree_is_balanced)
		{
			if (node == NULL)
			{
				tree_is_balanced = true;
				return NULL;
			}

			/* Current node is not the node to be erased */
			if (node->get_data() != data)
			{
				bool direction = data > node->get_data();
				node->get_children()[direction] = _erase(node->get_children()[direction], data, tree_is_balanced);

				if (!tree_is_balanced)
					return _erase_fix(node, direction, tree_is_balanced);

				return node;
			}

			/// found the delete key
			if (node->get_children_count() <= 1)
			{
				return _erase_key(node, tree_is_balanced, data);
			}

			if (node->get_children_count() == 2)
			{
				_erase_key(node, tree_is_balanced, data);
			}

			bool direction = data > node->get_data();
			node->get_children()[direction] = _erase(node->get_children()[direction], data, tree_is_balanced); /// recurse

			if (!tree_is_balanced)
				return _erase_fix(node, direction, tree_is_balanced);

			return node;
		}

		/* Constructors */
	public:
		/**
		 * @brief Construct a new red black tree object
		 * 
		 */
		red_black_tree()
		{
			this->_root = NULL;
		}

		explicit red_black_tree(const value_type &data)
		{
			this->_root = NULL;
			this->insert(data);
		}
		/* Destructors */
	public:
		/* Public Member Functions */
	public:
		/* Iterator functions */
	public:
		/* Capacity functions */
	public:
		/* Element access functions */
	public:
		/* Modifiers functions */
	public:
		/**
		 * @brief Insert data into the Red Black Tree
		 *
		 * @param data The Data to insert
		 */
		inline void insert(value_type data)
		{
			_root = _insert(_root, data);
			node_type::set_color(this->_root, node_type::black);
		}

		/**
		 * @brief Erases data from the Red Black Tree
		 * @param data The Data to erase
		 */
		inline void erase(value_type data)
		{
			bool tree_is_balanced = false;
			this->_root = _erase(this->_root, data, tree_is_balanced);
			node_type::set_color(this->_root, node_type::black);
		}

	};
} // namespace ft
