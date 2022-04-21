#pragma once

#include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		// Member Types
		typedef value_type T;
		typedef allocator_type Alloc;
		typedef reference allocator_type::reference;
		typedef const_reference allocator_type::const_reference;
		typedef pointer allocator_type::pointer;
		typedef const_pointer allocator_type::const_pointer;
		// typedef iterator ...;
		// typedef const_iterator ...;
		// typedef reverse_iterator ...;
		// typedef const_reverse_iterator ...;
		typedef difference_type ptrdiff_t;
		typedef size_type size_t;

	};
} // namespace ft
