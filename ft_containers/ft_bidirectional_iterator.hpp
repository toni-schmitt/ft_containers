#pragma once

#include <iterator>
#include <stddef.h>
#include "ft_forward_iterator.hpp"

namespace ft
{
	template <class T>
	class bidirectional_iterator : public forward_iterator
	{
		/* Iterator Tags ( == Member Types? ) */
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference = &value_type;
		using const_reference = const &value_type;
		using pointer = *value_type;
		using const_pointer = const *value_type;

		/* Constructors: */
		bidirectional_iterator() : forward_iterator();
		bidirectional_iterator(pointer ptr) : forward_iterator(ptr);
		bidirectional_iterator(const bidirectional_iterator &cpy) : forward_iterator(cpy);

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
