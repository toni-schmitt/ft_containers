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

		/* Constructors */
	public:
		/**
		 * @brief Construct a new red black tree object
		 */
		red_black_tree()
		{
			this->_root = NULL;
		}

		explicit red_black_tree(const value_type &data)
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
