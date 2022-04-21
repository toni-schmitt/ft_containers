#pragma once

#include <iterator>
#include <cstddef>
#include "ft_bidirectional_iterator.hpp"

namespace ft
{
	template <class T>
	class random_access_iterator : public bidirectional_iterator<T>
	{
		/* Iterator Tags ( == Member Types? ) */
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference = &value_type;
		using const_reference = const &value_type;
		using pointer = *value_type;
		using const_pointer = const *value_type;

		/* Constructors: */
		random_access_iterator() : bidirectional_iterator(NULL);
		random_access_iterator(pointer ptr) : bidirectional_iterator(ptr);
		random_access_iterator(const random_access_iterator &cpy) : bidirectional_iterator(cpy);

		/* Destructors: */
		~random_access_iterator();

		/* Arithretmic Operators */
		random_access_iterator operator+(difference_type n) const { return this->_ptr + n; }
		random_access_iterator operator-(difference_type n) const { return this->_ptr - n; }
		difference_type operator-(const random_access_iterator &b) const { return this->_ptr - b_ptr; }

		/* Comparison Operators */
		friend bool operator<(const random_access_iterator &a, const random_access_iterator &b) { return a._ptr < b._ptr; }
		friend bool operator>(const random_access_iterator &a, const random_access_iterator &b) { return a._ptr > b._ptr; }
		friend bool operator>=(const random_access_iterator &a, const random_access_iterator &b) { return a._ptr >= b._ptr; }
		friend bool operator<=(const random_access_iterator &a, const random_access_iterator &b) { return a._ptr <= b._ptr; }

		/* Compound Assignment Operators */
		random_access_iterator operator+=(difference_type n)
		{
			this->_ptr += n;
			return *this;
		}
		random_access_iterator operator-=(difference_type n)
		{
			this->_ptr -= n;
			return *this;
		}

		/* Offset Compound Operator */
		reference operator[](difference_type n) const { return this->_ptr[n]; }
	};
} // namespace ft
