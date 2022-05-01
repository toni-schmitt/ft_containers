#pragma once

#include <iterator>
#include <cstddef>
#include "bidirectional_iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Container>
	class random_access_iterator : public bidirectional_iterator<T, Container>
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
		random_access_iterator() : bidirectional_iterator<T, Container>(NULL) {}
		explicit random_access_iterator(pointer ptr) : random_access_iterator::bidirectional_iterator(ptr) {}
		random_access_iterator(const random_access_iterator<typename Container::value_type, Container> &cpy) : bidirectional_iterator<T, Container>(cpy) {}

	public:
		/* Destructors: */
		~random_access_iterator() {}

	public:
		/* Arithmetic Operators */
		random_access_iterator operator+(difference_type n) const { return random_access_iterator(this->_ptr + n); }
		random_access_iterator operator-(difference_type n) const { return random_access_iterator(this->_ptr - n); }
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
	template <class T, class Container>
	bool operator<(const random_access_iterator<T, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() < rhs.base(); }
	template <class T, class Container>
	bool operator<(const random_access_iterator<const typename Container::value_type, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() < rhs.base(); }
	template <class T, class Container>
	bool operator<(const random_access_iterator<T, Container> &lhs, const random_access_iterator<const typename Container::value_type, Container> &rhs) { return lhs.base() < rhs.base(); }

	template <class T, class Container>
	bool operator>(const random_access_iterator<T, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() > rhs.base(); }
	template <class T, class Container>
	bool operator>(const random_access_iterator<const typename Container::value_type, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() > rhs.base(); }
	template <class T, class Container>
	bool operator>(const random_access_iterator<T, Container> &lhs, const random_access_iterator<const typename Container::value_type, Container> &rhs) { return lhs.base() > rhs.base(); }

	template <class T, class Container>
	bool operator<=(const random_access_iterator<T, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() <= rhs.base(); }
	template <class T, class Container>
	bool operator<=(const random_access_iterator<const typename Container::value_type, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() <= rhs.base(); }
	template <class T, class Container>
	bool operator<=(const random_access_iterator<T, Container> &lhs, const random_access_iterator<const typename Container::value_type, Container> &rhs) { return lhs.base() <= rhs.base(); }

	template <class T, class Container>
	bool operator>=(const random_access_iterator<T, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() >= rhs.base(); }
	template <class T, class Container>
	bool operator>=(const random_access_iterator<const typename Container::value_type, Container> &lhs, const random_access_iterator<T, Container> &rhs) { return lhs.base() >= rhs.base(); }
	template <class T, class Container>
	bool operator>=(const random_access_iterator<T, Container> &lhs, const random_access_iterator<const typename Container::value_type, Container> &rhs) { return lhs.base() >= rhs.base(); }
} // namespace ft
