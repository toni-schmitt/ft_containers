#pragma once

#include <memory>
#include <cstddef>
#include <stdint.h>

static bool is_null(void *self)
{
	return self == NULL;
}

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
			RED = 0,
			BLACK = 1
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
				node_ptr parent, value_type data, node_color color = BLACK, node_ptr left_child = NULL,
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

	public:
		inline bool is_red()
		{
			if (is_null(this))
				return (false);

			return _color != BLACK;
		}

		inline bool is_black()
		{
			if (is_null(this))
				return (false);

			return _color != RED;
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
			if (is_null(this))
				return;

			if (this->_color == BLACK)
				this->_color = RED;
			else if (this->_color == RED)
				this->_color = BLACK;
		}

	public:
		/* Getter */
		inline node_ptr get_parent()
		{
			if (is_null(this))
				return node_ptr();

			return this->_parent;
		}

		inline value_type get_data()
		{
			if (is_null(this))
				return value_type();

			return this->_data;
		}

		inline node_color get_color()
		{
			if (is_null(this))
				return node_color();

			return this->_color;
		}

		inline node_ptr get_left_child()
		{
			if (is_null(this))
				return node_ptr();

			return this->_left_child;
		}

		inline node_ptr get_right_child()
		{
			if (is_null(this))
				return node_ptr();

			return this->_right_child;
		}

		inline node_ptr get_aunt()
		{
			if (is_null(this))
				return node_ptr();

			node_ptr parent = this->get_parent();
			node_ptr grand_parent = parent->get_parent();

			if (parent == grand_parent->get_left_child())
				return grand_parent->get_right_child();
			if (parent == grand_parent->get_right_child())
				return grand_parent->get_left_child();
			return NULL;
		}

		inline node_ptr get_sibling()
		{
			if (is_null(this))
				return node_ptr();

			node_ptr parent = this->get_parent();
			if (parent == NULL)
				return node_ptr();

			if (this == parent->get_left_child())
				return parent->get_right_child();
			if (this == parent->get_right_child())
				return parent->get_left_child();
			return NULL;
		}

		inline int get_children_count()
		{
			if (is_null(this))
				return int();

			int count = 0;
			if (this->_left_child != NULL)
				count += 1;
			if (this->_right_child != NULL)
				count += 1;
			return count;
		}

		/* Setter */
	public:
		inline void set_left_child(node_ptr left_child)
		{
			if (is_null(this))
				throw std::logic_error("Cannot dereference if this is NULL");
			if (left_child == NULL)
				return;

			this->_left_child = left_child;
		}

		inline void set_right_child(node_ptr right_child)
		{
			if (is_null(this))
				throw std::logic_error("Cannot dereference if this is NULL");
			if (right_child == NULL)
				return;

			this->_right_child = right_child;
		}

		inline void set_parent(node_ptr parent)
		{
			if (is_null(this))
				throw std::logic_error("Cannot dereference if this is NULL");
			if (parent == NULL)
				return;

			this->_parent = parent;
		}

		inline void set_color(node_color color)
		{
			if (is_null(this))
				throw std::logic_error("Cannot dereference if this is NULL");

			this->_color = color;
		}


		/* Special Modifier functions */
	public:
		inline void reset_parent()
		{
			if (is_null(this))
				return;

			this->_parent = NULL;
		}

		inline void reset_left_child()
		{
			if (is_null(this))
				return;

			this->_left_child = NULL;
		}

		inline void reset_right_child()
		{
			if (is_null(this))
				return;
			this->_right_child = NULL;
		}
	};

	/**
	 * Represents a NIL-Leaf Node
	 * @tparam T
	 * @tparam Alloc
	 */
	template < class T, class Alloc = std::allocator<T> >
	struct rbt_nil_node : public rbt_node<T>
	{
		/* Constructor */
	public:
		rbt_nil_node() : rbt_node<T>(NULL, 0, this->BLACK, NULL, NULL)
		{
			this->set_color(this->BLACK);
		}
	};
} // namespace ft
