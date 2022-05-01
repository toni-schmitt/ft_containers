#pragma once

#include <iterator>
#include <cstddef>
#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Container>
	class forward_iterator
	{
	public:
		/* Iterator Tags ( == Member Types? ) */
		typedef ft::forward_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;

	public:
		/* Constructors: */
		forward_iterator() : _ptr(NULL){};
		explicit forward_iterator(pointer ptr) : _ptr(ptr){};
		forward_iterator(const forward_iterator<typename Container::value_type, Container> &cpy) : _ptr(cpy.base()){};

	public:
		/* Destructors: */
		~forward_iterator() {}

	public:
		/* Overloaded Operators */
		forward_iterator &operator=(const forward_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_ptr = sec._ptr;

			return *this;
		};

	public:
		/* Dereference Operators */
		reference operator*() const { return *this->_ptr; }
		pointer operator->() const { return this->_ptr; }

	public:
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

	public:
		/* Member Functions */
		pointer base() const { return this->_ptr; }

	protected:
		pointer _ptr;
	};

	/* Comparison Operators */
	template <class T, class Container>
	bool operator==(const forward_iterator<T, Container> &lhs, const forward_iterator<T, Container> &rhs) { return lhs.base() == rhs.base(); }
	template <class T, class Container>
	bool operator==(const forward_iterator<const typename Container::value_type, Container> &lhs, const forward_iterator<T, Container> &rhs) { return lhs.base() == rhs.base(); }
	template <class T, class Container>
	bool operator==(const forward_iterator<T, Container> &lhs, const forward_iterator<const typename Container::value_type, Container> &rhs) { return lhs.base() == rhs.base(); }

	template <class T, class Container>
	bool operator!=(const forward_iterator<T, Container> &lhs, const forward_iterator<T, Container> &rhs) { return lhs.base() != rhs.base(); }
	template <class T, class Container>
	bool operator!=(const forward_iterator<const typename Container::value_type, Container> &lhs, const forward_iterator<T, Container> &rhs) { return lhs.base() != rhs.base(); }
	template <class T, class Container>
	bool operator!=(const forward_iterator<T, Container> &lhs, const forward_iterator<const typename Container::value_type, Container> &rhs) { return lhs.base() != rhs.base(); }
} // namespace ft