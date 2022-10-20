#pragma once

#include "map_iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template < class T, class Container, class Tree >
	class rbt_iterator
	{
		/* Iterator Tags */
	public:
		typedef bidirectional_iterator_tag iterator_category;
	private:
		typedef Tree tree_type;
	public:
		typedef typename tree_type::value_type value_type;
		typedef typename tree_type::difference_type difference_type;
		typedef typename tree_type::reference reference;
		typedef typename tree_type::pointer pointer;
		typedef typename tree_type::node_pointer node_pointer;

		/* Private Members */
	private:
		static node_pointer _nil_node;
		node_pointer _ptr;

		/* Constructors */
	public:
		rbt_iterator() : _ptr(_nil_node) { }

		explicit rbt_iterator(const node_pointer &ptr) : _ptr(ptr) { }

		rbt_iterator(const rbt_iterator &sec) : _ptr(sec._ptr) { }

		rbt_iterator(const bidirectional_iterator<T, Container, Tree> &iter) : _ptr(iter._base_iter()._ptr) { }

		/* Member Functions */
	public:
		node_pointer get_base_ptr() const { return this->_ptr; }

		/* Iterator Operations */

		/* Overloaded Operators */
	public:
		rbt_iterator &operator=(const rbt_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_ptr = sec._ptr;

			return *this;
		}

		/* Dereference Operators */
	public:
		reference operator*() const { return this->_ptr->value; }

		pointer operator->() const { return &(operator*()); }

		/* Increment Operators */
	public:
		rbt_iterator &operator++()
		{
			if (_ptr != _nil_node && _ptr && _ptr->right && _ptr->right != _nil_node)
				_ptr = rb_min(_ptr->right);
			else
			{
				node_pointer y = _ptr->parent;
				while (y != _nil_node && y->parent != NULL && _ptr == y->right)
				{
					_ptr = y;
					y = y->parent;
				}
				_ptr = y;
			}
			return *this;
		}

		rbt_iterator operator++(int)
		{
			node_pointer old = _ptr;
			++*this;
			return rbt_iterator(old);
		}

		/* Decrement Operators */
	public:
		rbt_iterator &operator--()
		{
			if (_ptr != _nil_node && _ptr && _ptr->left && _ptr->left != _nil_node)
				_ptr = rb_max(_ptr->left);
			else
			{

				node_pointer y = _ptr->parent;
				while (y != _nil_node && y->parent != NULL && y->parent != _nil_node && _ptr == y->left)
				{
					_ptr = y;
					y = y->parent;
				}
				_ptr = y;
			}
			return *this;
		}

		rbt_iterator operator--(int)
		{
			node_pointer old = _ptr;
			--*this;
			return rbt_iterator(old);
		}
	};

	/* Comparison Operators */
	template < class T, class Container, class Tree >
	bool operator==(const rbt_iterator<T, Container, Tree> &lhs,
					const rbt_iterator<T, Container, Tree> &rhs) { return lhs.get_base_ptr() == rhs.get_base_ptr(); }

	template < class T, class Container, class Tree >
	bool operator==(const rbt_iterator<const typename Tree::value_type, Container, Tree> &lhs,
					const rbt_iterator<T, Container, Tree> &rhs) { return lhs.get_base_ptr() == rhs.get_base_ptr(); }

	template < class T, class Container, class Tree >
	bool operator==(const rbt_iterator<T, Container, Tree> &lhs,
					const rbt_iterator<const typename Tree::value_type, Container, Tree> &rhs)
	{
		return lhs.get_base_ptr() == rhs.get_base_ptr();
	}

	template < class T, class Container, class Tree >
	bool operator!=(const rbt_iterator<T, Container, Tree> &lhs,
					const rbt_iterator<T, Container, Tree> &rhs) { return lhs.get_base_ptr() != rhs.get_base_ptr(); }

	template < class T, class Container, class Tree >
	bool operator!=(const rbt_iterator<const typename Tree::value_type, Container, Tree> &lhs,
					const rbt_iterator<T, Container, Tree> &rhs) { return lhs.get_base_ptr() != rhs.get_base_ptr(); }

	template < class T, class Container, class Tree >
	bool operator!=(const rbt_iterator<T, Container, Tree> &lhs,
					const rbt_iterator<const typename Tree::value_type, Container, Tree> &rhs)
	{
		return lhs.get_base_ptr() != rhs.get_base_ptr();
	}

	template < class T, class Container, class Tree >
	typename rbt_iterator<T, Container, Tree>::node_pointer rbt_iterator<T, Container, Tree>::_nil_node = typename rbt_iterator<T, Container, Tree>::node_pointer();
}