#pragma once

#include <memory>
#include <cstdlib>

#define rbt_node_left_child 0
#define rbt_node_right_child 1

namespace ft
{

	/**
	 * @brief Node Structor for Red Black Tree
	 *
	 * @tparam T Value Type of Node Data
	 * @tparam Alloc Allocator of Value Type (Defaults to std::allocator<T>)
	 */
	template <class T, class Alloc = std::allocator<T> >
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
		value_type data;
		node_ptr children[2];
		node_color color;

		/* Private Functions */
	private:
		/**
		 * @brief Flips color of node
		 *
		 * @param node Node of which to flip color
		 */
		void _flip_color(node_ptr node)
		{
			if (node == NULL)
				return;

			node->color = node->color == red ? black : red;
		}

		/* Constructors */
	public:
		/**
		 * @brief Construct a new rbt node object
		 *
		 * @param data Data to store in Node
		 * @param color Color of Node (see enum node_color)
		 * @param left_child Left Child of Node
		 * @param right_child Right Child of Node
		 */
		rbt_node(value_const_ref data, node_color color, node_ptr left_child = NULL, node_ptr right_child = NULL)
		{
			this->data = data;
			this->children[rbt_node_left_child] = left_child;
			this->children[rbt_node_right_child] = right_child;
			this->color = color;
		}

		/**
		 * @brief Construct a new rbt node object from copy
		 *
		 * @param copy Copy of which to construct object
		 */
		rbt_node(const_node_ref copy)
		{
			if (&copy == this)
				return;

			this->data = copy.data;
			this->color = copy.color;
			this->children = copy.children;

		}

		/* Destructors */
	public:
		~rbt_node() { }

		/* Modifiers functions */
	public:
		/**
		 * @brief Flips color of this node
		 *
		 */
		void flip_color()
		{
			_flip_color(this);
			_flip_color(this->children[rbt_node_left_child]);
			_flip_color(this->children[rbt_node_right_child]);
		}

	public:
		bool is_red() { return this->color == red; }

		static bool is_red(node_ptr node)
		{
			if (node == NULL)
				return false;
			return node->is_red();
		}

		bool is_black() { return this->color == black; }

		static bool is_black(node_ptr node)
		{
			if (node == NULL)
				return false;
			return node->is_black();
		}

		bool has_left_child() { return this->get_left_child() != NULL; }

		bool has_right_child() { return this->get_right_child() != NULL; }

	public:
		/* Getter */
		value_type get_data() { return this->data; }

		node_ptr *get_children() { return this->children; }

		uint get_children_count()
		{
			uint count = 0;
			for (int i = 0; this->children[i]; ++i)
				++count;
			return count;
		}

		node_ptr get_left_child() { return this->children[rbt_node_left_child]; }

		node_ptr get_right_child() { return this->children[rbt_node_right_child]; }

		node_color get_color() { return this->color; }

		/* Setter */
		void set_data(value_type new_data) { this->data = new_data; }

		void set_children(node_ptr new_children[2]) { this->children = new_children; }

		void set_color(node_color new_color) { this->color = new_color; }
	};

	// search, insert, delete (main operations)
	// helpers: rotation, color flip
	template <class T, class Alloc = std::allocator<T> >
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
		void _color_flip(node_ptr node)
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
		node_ptr _rotate(node_ptr node, bool direction)
		{

			node_ptr tmp = node->get_children()[!direction];
			//node->set_child(!direction, tmp->get_children()[direction]);
			node->get_children()[!direction] = tmp
					->get_children()[direction]; // Opposite child = Opposite childs direction (left/right) child
			//tmp->set_child(direction, node);
			tmp->get_children()[direction] = node;

			tmp->set_color(node->get_color());
			node->set_color(node_type::red);

			return tmp;
		}

		node_ptr _double_rotate(node_ptr node, bool direction)
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

		node_ptr _insert(node_ptr node, value_type data)
		{
			if (node == NULL)
				return new node_type(data, node_type::red);

			bool direction = data > node->get_data();

			node->get_children()[direction] = _insert(node->get_children()[direction], data);

			return _insert_fix(node, direction);
		}


		// Assumes that node only has one or fewer children
		node_ptr get_available_child(node_ptr node)
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
				else if (available_child->is_red())
				{
					available_child->set_color(node_type::black);
					delete key;
					tree_is_balanced = true;
				}

				return available_child;
			}

			if (key->get_children_count() == 2)
			{
				node_ptr tmp = node_type::get_max(key->get_left_child());

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

			if (sibling->is_red())
			{
				node = _rotate(node, direction);
				sibling = parent->get_children()[!direction];
			}

			if (sibling == NULL)
				return node;

			if (!sibling->get_left_child()->is_red() && !sibling->get_right_child()->is_red())
			{
				if (parent->is_red())
					tree_is_balanced = true;

				parent->set_color(node_type::black);
				sibling->set_color(node_type::red);
				return node;
			}

			node_color initial_color_parent = parent->get_color();
			bool is_red_sibling_reduction = !(node == parent);

			if (sibling->get_children()[!direction]->is_red())
			{
				parent = _rotate(parent, direction);
			}
			else
			{
				parent = _double_rotate(parent, direction);
			}

			parent->set_color(initial_color_parent);
			parent->get_left_child()->set_color(node_type::black);
			parent->get_right_child()->set_color(node_type::black);

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

		node_ptr _erase(node_ptr node, value_type data, bool &tree_is_balanced)
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
			node->child[direction] = _erase(node->get_children()[direction], data, tree_is_balanced); /// recurse

			if (!tree_is_balanced)
				return _erase_fix(node, direction, tree_is_balanced);

			return node;
		}

		/* Constructors */
	public:
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
		void insert(value_type data)
		{
			_root = _insert(_root, data);
			_root->set_color(node_type::black);
		}

		/**
		 * @brief Erases data from the Red Black Tree
		 * @param data The Data to erase
		 */
		void erase(value_type data)
		{
			bool tree_is_balanced = false;
			this->_root = _erase(this->_root, data, tree_is_balanced);
			if (this->_root != NULL)
				this->_root->set_color(node_type::black);
		}

	};
} // namespace ft
