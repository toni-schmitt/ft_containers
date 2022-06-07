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

			node->color = node->color ^ 1;
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
				return *this;

			this->data = copy.data;
			this->color = copy.color;
			this->children = copy.children;

			return *this;
		}

		/* Destructors */
	public:
		~rbt_node() {}

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
			const node_ptr opposite_child = node.children[!direction];

			node_ptr tmp = opposite_child;
			opposite_child = tmp->children[direction]; // Opposite child = Opposite childs direction (left/right) child
			tmp->children[direction] = node;

			tmp->color = node->color;
			node->color = node_color::red;

			return tmp;
		}

		node_ptr _double_rotate(node_ptr node, bool direction)
		{
			node->children[direction] = _rotate(node->children[!direction], !direction);
			return _rotate(node, direction);
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
	};
} // namespace ft
