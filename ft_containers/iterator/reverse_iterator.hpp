#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template < class Iterator >
	class reverse_iterator
	{
	public:
		/* Member Types */
		typedef Iterator iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;

	public:
		/* Constructors */
		reverse_iterator() : _base_iter() { }

		explicit reverse_iterator(iterator_type it) : _base_iter(it) { }

		template < class Iter >
		reverse_iterator(const reverse_iterator<Iter> &copy) : _base_iter(copy.base()) { }

	public:
		/* Destructor */
		~reverse_iterator() { }

	public:
		/* Overloaded Operators */
		reverse_iterator &operator=(const reverse_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_base_iter = sec._base_iter;

			return *this;
		}

	public:
		/* Dereference Operators */
		reference operator*() { return *(--_base_iter); }

		reference operator*() const { return *(--_base_iter); }

		pointer operator->() { return &(this->operator*()); }

		pointer operator->() const { return &(this->operator*()); }

	public:
		/* Increment Operators */
		reverse_iterator &operator++()
		{
			--_base_iter;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

	public:
		/* Decrement Operators */
		reverse_iterator &operator--()
		{
			++_base_iter;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

	public:
		/* Arithmetic Operators */
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_base_iter - n); }

		difference_type operator-(const reverse_iterator &rhs) const { return rhs._base_iter - this->_base_iter; }

		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_base_iter + n); }

	public:
		/* Compound Assignment Operators */
		reverse_iterator &operator+=(difference_type n)
		{
			this->_base_iter -= n;
			return *this;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->_base_iter += n;
			return *this;
		}

	public:
		/* Offset Compound Operator */
		reference operator[](difference_type n) const { return this->base()[ -n - 1 ]; }

	public:
		/* Member Functions */
		iterator_type base() const { return this->_base_iter; }

	private:
		iterator_type _base_iter;
	};

	/* Arithmetic Operators */
	template < class Iterator >
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
										 const reverse_iterator<Iterator> &rev_iter) { return rev_iter + n; }

	template < class Iterator >
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
										 const reverse_iterator<Iterator> &rev_iter) { return rev_iter - n; }

	/* Comparison Operators */
	template < class Iterator >
	bool operator==(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template < class Iterator_L, class Iterator_R >
	bool operator==(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template < class Iterator >
	bool operator!=(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template < class Iterator_L, class Iterator_R >
	bool operator!=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template < class Iterator >
	bool operator<(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template < class Iterator_L, class Iterator_R >
	bool operator<(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template < class Iterator >
	bool operator<=(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template < class Iterator_L, class Iterator_R >
	bool operator<=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template < class Iterator >
	bool operator>(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template < class Iterator_L, class Iterator_R >
	bool operator>(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template < class Iterator >
	bool operator>=(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator> const &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template < class Iterator_L, class Iterator_R >
	bool operator>=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

} // namespace ft
