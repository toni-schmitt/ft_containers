#pragma once

#include <iterator>
#include <cstddef>
#include "ft_bidirectional_iterator.hpp"
#include "ft_iterator_traits.hpp"

namespace ft
{
	template <class T>
	class random_access_iterator : public bidirectional_iterator<T>
	{
	public:
		/* Iterator Tags ( == Member Types? ) */
		typedef random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;

	public:
		/* Constructors: */
		random_access_iterator() : bidirectional_iterator<T>(NULL) {}
		explicit random_access_iterator(pointer ptr) : bidirectional_iterator<T>(ptr) {}
		random_access_iterator(const random_access_iterator &cpy) : bidirectional_iterator<T>(cpy) {}

	public:
		/* Destructors: */
		~random_access_iterator() {}

	public:
		/* Arithretmic Operators */
		random_access_iterator operator+(difference_type n) const { return this->_ptr + n; }
		random_access_iterator operator-(difference_type n) const { return this->_ptr - n; }
		difference_type operator-(const random_access_iterator &b) const { return this->_ptr - b.base(); }

	public:
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

	public:
		/* Offset Compound Operator */
		reference operator[](difference_type n) const { return this->_ptr[n]; }
	};

	/* Comparison Operators */
	template <class T>
	bool operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() < rhs.base(); }
	template <class T>
	bool operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() > rhs.base(); }
	template <class T>
	bool operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() <= rhs.base(); }
	template <class T>
	bool operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs) { return lhs.base() >= rhs.base(); }
} // namespace ft
