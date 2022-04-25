#pragma once

#include <iterator>
#include <stddef.h>
#include "ft_iterator_traits.hpp"

namespace ft
{
	template <class T>
	class forward_iterator
	{
		/* Iterator Tags ( == Member Types? ) */
		typedef ft::forward_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		/* Constructors: */
		forward_iterator() : _ptr(NULL) {};
		forward_iterator(pointer ptr) : _ptr(ptr) {};
		forward_iterator(const forward_iterator &cpy) : _ptr(cpy._ptr) {};

		/* Destructors: */
		~forward_iterator();

		/* Overloaded Operators */
		forward_iterator &operator=(const forward_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_ptr = sec._ptr;

			return *this;
		};

		/* Derefernece Operators */
		reference operator*() const { return *this->_ptr; }
		pointer operator->() const { return this->_ptr; }

		/* Increment Operators */
		forward_iterator &operator++()
		{
			this->_ptr++;
			return *this;
		}
		forward_iterator operator++(T)
		{
			forward_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		/* Member Functions */
		pointer base() const { return this->_ptr; }

	protected:
		pointer _ptr;
	};

	/* Comparison Operators */
	template <class T>
	bool operator==(const forward_iterator<T> &lhs, const forward_iterator<T> &rhs) { return lhs.base() == rhs.base(); }
	template <class T>
	bool operator!=(const forward_iterator<T> &lhs, const forward_iterator<T> &rhs) { return lhs.base() != rhs.base(); }
} // namespace ft
