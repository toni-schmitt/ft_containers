#pragma once

#include <memory>

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

		/* Private Members */
	private:
		const caller_type &_caller_class;

		/* Constructor */
	public:
		explicit rbt_eraser(const caller_type &caller_class) : _caller_class(caller_class) { }

		/* Public Member Functions */
	public:
		bool erase(const node_ptr &to_erase)
		{
			(void) to_erase;
			return true;
		}

		bool erase(const value_type &data)
		{
			(void) data;
			return true;
		}

	private:
	};
} // namespace ft