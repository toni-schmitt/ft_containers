#pragma once

#include "iterator_traits.hpp"
#include <iterator>

namespace ft
{
	template < class InputIterator >
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return std::distance(first, last);
	}

	template < class Iterator >
	typename iterator_traits<Iterator>::pointer get_raw_pointer(Iterator iter)
	{
		return iter.base();
	}

	template < class InputIterator >
	void advance(InputIterator &i, typename iterator_traits<InputIterator>::difference_type n)
	{
		std::advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
	}

	template < class Iterator >
	Iterator next(Iterator it,
				  typename iterator_traits<Iterator>::difference_type n = 1)
	{
		ft::advance(it, n);
		return it;
	}

} // namespace ft
