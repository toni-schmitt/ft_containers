#pragma once

#include <iterator>
#include <stddef.h>
#include "ft_forward_iterator.hpp"
#include "ft_iterator_traits.hpp"

namespace ft
{
	template <class T>
	class bidirectional_iterator : public forward_iterator<T>
	{
		/* Iterator Tags ( == Member Types? ) */
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		/* Constructors: */
		bidirectional_iterator() : forward_iterator<T>() {}
		bidirectional_iterator(pointer ptr) : forward_iterator<T>(ptr) {}
		bidirectional_iterator(const bidirectional_iterator &cpy) : forward_iterator<T>(cpy) {}

		/* Destructors: */
		~bidirectional_iterator();

		/* Decrement Operators */
		bidirectional_iterator &operator--()
		{
			this->_ptr--;
			return *this;
		}
		bidirectional_iterator operator--(T)
		{
			bidirectional_iterator tmp = *this;
			--(*this);
			return tmp;
		}
	};
} // namespace ft
