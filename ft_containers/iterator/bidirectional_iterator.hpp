#pragma once

#include <iterator>
#include <cstddef>
#include "forward_iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Container>
	class bidirectional_iterator : public forward_iterator<T, Container>
	{
	public:
		/* Iterator Tags ( == Member Types? ) */
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;

	public:
		/* Constructors: */
		bidirectional_iterator() : forward_iterator<T, Container>() {}
		explicit bidirectional_iterator(pointer ptr) : bidirectional_iterator::forward_iterator(ptr) {}
		bidirectional_iterator(const bidirectional_iterator<typename Container::value_type, Container> &cpy) : forward_iterator<T, Container>(cpy) {}

	public:
		/* Destructors: */
		~bidirectional_iterator() {}

	public:
		/* Decrement Operators */
		bidirectional_iterator &operator--()
		{
			this->_ptr--;
			return *this;
		}
		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp = *this;
			--(*this);
			return tmp;
		}
	};
} // namespace ft
