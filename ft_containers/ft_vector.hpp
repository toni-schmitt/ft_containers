#pragma once

#include <memory>
#include "ft_random_access_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		// Member Types
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		// typedef const_iterator ...;
		// typedef reverse_iterator ...;
		// typedef const_reverse_iterator ...;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

	};
} // namespace ft
