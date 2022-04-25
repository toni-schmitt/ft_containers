#pragma once

#include "ft_iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		/* Member Types */
		typedef Iterator iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;

		/* Constructors */
		reverse_iterator() : _baseIter() {}
		explicit reverse_iterator(iterator_type it) : _baseIter(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &copy) : _baseIter(copy.base()) {}

		/* Deconstrutors */
		~reverse_iterator();

		/* Derefernece Operators */
		reference operator*() const { return *this->_baseIter; }
		pointer operator->() const { return this->_baseIter; }

		/* Increment Operators */
		reverse_iterator &operator++()
		{
			_baseIter--;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		/* Decrement Operators */
		reverse_iterator &operator--()
		{
			_baseIter++;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		/* Arithmetic Operators */
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_baseIter - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_baseIter + n); }

		/* Compound Assignment Operators */
		reverse_iterator &operator+=(difference_type n)
		{
			this->_baseIter -= n;
			return *this;
		}
		reverse_iterator &operator-=(difference_type n)
		{
			this->_baseIter += n;
			return *this;
		}

		/* Offset Compound Operator */
		reference operator[](difference_type n) const { return this->base()[-n - 1]; }

		/* Member Functions */
		iterator_type base() const { return this->_baseIter; }

	private:
		iterator_type _baseIter;
	};

	/* Arithmetic Operators */
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_iter) { return rev_iter + n; }
	template <class Iterator>
	reverse_iterator<Iterator> operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs - rhs; }

	/* Comparison Operators */
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs.base() == rhs.base(); }

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs.base() != rhs.base(); }

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs.base() > rhs.base(); }

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs.base() >= rhs.base(); }

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs.base() < rhs.base(); }

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return lhs.base() <= rhs.base(); }

} // namespace ft