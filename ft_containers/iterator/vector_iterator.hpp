#pragma once

#include <iterator>
#include <cstddef>
#include "iterator_traits.hpp"

namespace ft
{
	/* Iterator System */
	/* Random Access Iterator */
	template < class T, class Container >
	class random_access_iterator
	{
		/* Iterator Tags */
	public:
		typedef random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;

		/* Private Members */
	private:
		pointer _ptr;

		/* Constructors */
	public:
		random_access_iterator() : _ptr(NULL) { }

		explicit random_access_iterator(pointer ptr) : _ptr(ptr) { }

		random_access_iterator(const random_access_iterator<typename Container::value_type, Container> &cpy) : _ptr(
				cpy.base()) { }

		/* Destructors */
	public:
		~random_access_iterator() { }

		/* Member Functions */
	public:
		pointer base() const { return this->_ptr; }

		/* Iterator Operations */

		/* Overloaded Operators */
	public:
		random_access_iterator &operator=(const random_access_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_ptr = sec._ptr;

			return *this;
		};

		/* Dereference Operators */
	public:
		reference operator*() const { return *this->_ptr; }

		pointer operator->() const { return this->_ptr; }

		/* Increment Operators */
	public:
		random_access_iterator &operator++()
		{
			this->_ptr++;
			return *this;
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		/* Decrement Operators */
	public:
		random_access_iterator &operator--()
		{
			this->_ptr--;
			return *this;
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		/* Arithmetic Operators */
	public:
		random_access_iterator operator+(difference_type n) const { return random_access_iterator(this->_ptr + n); }

		random_access_iterator operator-(difference_type n) const { return random_access_iterator(this->_ptr - n); }

		difference_type operator-(const random_access_iterator &b) const { return this->_ptr - b.base(); }

		/* Compound Assignment Operators */
	public:
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
	public:
		reference operator[](difference_type n) const { return this->_ptr[ n ]; }
	};

	/* Random Access Iterator Non-Member Overloads */

	/* Arithmetic Operators */
	template < class T, class Container >
	random_access_iterator<T, Container> operator+(typename random_access_iterator<T, Container>::difference_type n,
												   const random_access_iterator<T, Container> &rand_acc_iter)
	{
		return random_access_iterator<T, Container>(rand_acc_iter.base() + n);
	}

	template < class T, class Container >
	random_access_iterator<T, Container> operator-(typename random_access_iterator<T, Container>::difference_type n,
												   const random_access_iterator<T, Container> &rand_acc_iter)
	{
		return random_access_iterator<T, Container>(rand_acc_iter.base() - n);
	}

	/* Comparison Operators */
	template < class T, class Container >
	bool operator==(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() == rhs.base(); }

	template < class T, class Container >
	bool operator==(const random_access_iterator<const typename Container::value_type, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() == rhs.base(); }

	template < class T, class Container >
	bool operator==(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<const typename Container::value_type, Container> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template < class T, class Container >
	bool operator!=(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() != rhs.base(); }

	template < class T, class Container >
	bool operator!=(const random_access_iterator<const typename Container::value_type, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() != rhs.base(); }

	template < class T, class Container >
	bool operator!=(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<const typename Container::value_type, Container> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template < class T, class Container >
	bool operator<(const random_access_iterator<T, Container> &lhs, const random_access_iterator<T, Container> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template < class T, class Container >
	bool operator<(const random_access_iterator<const typename Container::value_type, Container> &lhs,
				   const random_access_iterator<T, Container> &rhs) { return lhs.base() < rhs.base(); }

	template < class T, class Container >
	bool operator<(const random_access_iterator<T, Container> &lhs,
				   const random_access_iterator<const typename Container::value_type, Container> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template < class T, class Container >
	bool operator>(const random_access_iterator<T, Container> &lhs, const random_access_iterator<T, Container> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template < class T, class Container >
	bool operator>(const random_access_iterator<const typename Container::value_type, Container> &lhs,
				   const random_access_iterator<T, Container> &rhs) { return lhs.base() > rhs.base(); }

	template < class T, class Container >
	bool operator>(const random_access_iterator<T, Container> &lhs,
				   const random_access_iterator<const typename Container::value_type, Container> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template < class T, class Container >
	bool operator<=(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() <= rhs.base(); }

	template < class T, class Container >
	bool operator<=(const random_access_iterator<const typename Container::value_type, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() <= rhs.base(); }

	template < class T, class Container >
	bool operator<=(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<const typename Container::value_type, Container> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template < class T, class Container >
	bool operator>=(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() >= rhs.base(); }

	template < class T, class Container >
	bool operator>=(const random_access_iterator<const typename Container::value_type, Container> &lhs,
					const random_access_iterator<T, Container> &rhs) { return lhs.base() >= rhs.base(); }

	template < class T, class Container >
	bool operator>=(const random_access_iterator<T, Container> &lhs,
					const random_access_iterator<const typename Container::value_type, Container> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

} // namespace ft
