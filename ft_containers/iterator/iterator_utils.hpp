#pragma once

#include "iterator_traits.hpp"

namespace ft
{

	/* Distance Function */
	/* For STD Iterators: */
	/* Input Iterator Template */
	template <class InputIterator>
	typename std::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		typename std::iterator_traits<InputIterator>::difference_type dist = 0;
		while (first != last)
		{
			++first;
			++dist;
		}
		return dist;
	}
	/* Random Access Iterator Template */
	template <class InputIterator>
	typename std::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, std::random_access_iterator_tag)
	{
		return last - first;
	}
	/* For FT Iterators: */
	/* Input Iterator Template */
	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type dist = 0;
		while (first != last)
		{
			++first;
			++dist;
		}
		return dist;
	}
	/* Random Access Iterator Template */
	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, random_access_iterator_tag)
	{
		return last - first;
	}
	/* Generic Template */
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return _distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
	}
} // namespace ft
