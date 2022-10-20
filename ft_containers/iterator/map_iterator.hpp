#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template < class T, class Container, class Tree >
	class bidirectional_iterator
	{
		/* Iterator Tags */
	public:
		typedef bidirectional_iterator_tag iterator_category;
	private:
		typedef typename Container::tree_iterator tree_iterator;
		typedef typename Container::tree_const_iterator tree_const_iterator;
	public:
		typedef typename tree_iterator::value_type value_type;
		typedef typename tree_iterator::difference_type difference_type;
		typedef typename tree_iterator::reference reference;
		typedef typename tree_iterator::pointer pointer;

		/* Private Members */
	private:
		tree_iterator _base_iter;

		/* Constructors */
	public:
		bidirectional_iterator() : _base_iter(tree_iterator(NULL)) { }

		bidirectional_iterator(const bidirectional_iterator &cpy) : _base_iter(cpy.base()) { }

		explicit bidirectional_iterator(tree_const_iterator const_tree_iter) : _base_iter(
				tree_iterator(const_tree_iter.get_base_ptr())) { }

		explicit bidirectional_iterator(tree_iterator tree_iter) : _base_iter(tree_iter) { }

		/* Destructors */
	public:
		~bidirectional_iterator() { }

		/* Member Functions */
	public:
		tree_iterator base() const { return this->_base_iter; }

		/* Iterator Operations */

		/* Overloaded Operators */
	public:
		bidirectional_iterator &operator=(const bidirectional_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_base_iter = sec._base_iter;

			return *this;
		}
		/* Dereference Operators */
	public:
		reference operator*() const { return *this->_base_iter; }

		pointer operator->() const { return this->_base_iter.operator->(); }

		/* Increment Operators */
	public:
		bidirectional_iterator &operator++()
		{
			this->_base_iter++;
			return *this;
		}

		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		/* Decrement Operators */
	public:
		bidirectional_iterator &operator--()
		{
			this->_base_iter--;
			return *this;
		}

		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp = *this;
			--(*this);
			return tmp;
		}
	};

	/* Comparison Operators */
	template < class T, class Container, class Tree >
	bool operator==(const bidirectional_iterator<T, Container, Tree> &lhs,
					const bidirectional_iterator<T, Container, Tree> &rhs) { return lhs.base() == rhs.base(); }

	template < class T, class Container, class Tree >
	bool operator==(const bidirectional_iterator<const typename Container::value_type, Container, Tree> &lhs,
					const bidirectional_iterator<T, Container, Tree> &rhs) { return lhs.base() == rhs.base(); }

	template < class T, class Container, class Tree >
	bool operator==(const bidirectional_iterator<T, Container, Tree> &lhs,
					const bidirectional_iterator<const typename Container::value_type, Container, Tree> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template < class T, class Container, class Tree >
	bool operator!=(const bidirectional_iterator<T, Container, Tree> &lhs,
					const bidirectional_iterator<T, Container, Tree> &rhs) { return lhs.base() != rhs.base(); }

	template < class T, class Container, class Tree >
	bool operator!=(const bidirectional_iterator<const typename Container::value_type, Container, Tree> &lhs,
					const bidirectional_iterator<T, Container, Tree> &rhs) { return lhs.base() != rhs.base(); }

	template < class T, class Container, class Tree >
	bool operator!=(const bidirectional_iterator<T, Container, Tree> &lhs,
					const bidirectional_iterator<const typename Container::value_type, Container, Tree> &rhs)
	{
		return lhs.base() != rhs.base();
	}
}