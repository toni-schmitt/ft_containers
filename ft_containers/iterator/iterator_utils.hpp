#pragma once

#include "iterator_traits.hpp"
#include <iterator>

namespace ft
{

	/* Distance Function */
	/* For STD Iterators: */
	/* Input Iterator Template */
	template <class InputIterator>
	typename std::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, std::input_iterator_tag)
	{
		return std::distance(first, last);
	}
	/* Random Access Iterator Template */
	template <class InputIterator>
	typename std::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, std::random_access_iterator_tag)
	{
		return std::distance(first, last);
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

	template <class Iterator>
	typename iterator_traits<Iterator>::pointer get_raw_pointer(Iterator iter)
	{
		return iter.base();
	}

	namespace
	{
		/* STD ITERATORS */

		template <class InputIterator>
		void _advance(InputIterator &i, typename iterator_traits<InputIterator>::difference_type n, std::input_iterator_tag)
		{
			return std::advance(i, n);
		}
		template <class BidirectionalIterator>
		void _advance(BidirectionalIterator &i, typename iterator_traits<BidirectionalIterator>::difference_type n, std::bidirectional_iterator_tag)
		{
			return std::advance(i, n);
		}
		template <class RandomAccessIterator>
		void _advance(RandomAccessIterator &i, typename iterator_traits<RandomAccessIterator>::difference_type n, std::random_access_iterator_tag)
		{
			return std::advance(i, n);
		}

		/* FT ITERATORS */

		template <class InputIterator>
		void _advance(InputIterator &i, typename iterator_traits<InputIterator>::difference_type n, ft::input_iterator_tag)
		{
			while (n > 0)
			{
				++i;
				--n;
			}
		}
		template <class BidirectionalIterator>
		void _advance(BidirectionalIterator &i, typename iterator_traits<BidirectionalIterator>::difference_type n, ft::bidirectional_iterator_tag)
		{
			if (n >= 0)
			{
				while (n > 0)
				{
					++i;
					--n;
				}
			}
			else
			{
				while (n < 0)
				{
					--i;
					++n;
				}
			}
		}
		template <class RandomAccessIterator>
		void _advance(RandomAccessIterator &i, typename iterator_traits<RandomAccessIterator>::difference_type n, ft::random_access_iterator_tag)
		{
			i += n;
		}
	} // private namespace

	template <class InputIterator>
	void advance(InputIterator &i, typename iterator_traits<InputIterator>::difference_type n)
	{
		_advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
	}

	namespace
	{

		/* STD ITERATORS */

		template <class InputIterator>
		InputIterator _next(InputIterator it, typename iterator_traits<InputIterator>::difference_type n, std::input_iterator_tag)
		{
			return std::next(it, n);
		}
		template <class BidirectionalIterator>
		BidirectionalIterator _next(BidirectionalIterator it, typename iterator_traits<BidirectionalIterator>::difference_type n, std::bidirectional_iterator_tag)
		{
			return std::next(it, n);
		}
		template <class RandomAccessIterator>
		RandomAccessIterator _next(RandomAccessIterator it, typename iterator_traits<RandomAccessIterator>::difference_type n, std::random_access_iterator_tag)
		{
			return std::next(it, n);
		}

		/* FT ITERATORS */

		template <class InputIterator>
		InputIterator _next(InputIterator it, typename iterator_traits<InputIterator>::difference_type n, ft::input_iterator_tag)
		{
			ft::advance(it, n);
			return it;
		}
		template <class BidirectionalIterator>
		BidirectionalIterator _next(BidirectionalIterator it, typename iterator_traits<BidirectionalIterator>::difference_type n, ft::bidirectional_iterator_tag)
		{
			ft::advance(it, n);
			return it;
		}
		template <class RandomAccessIterator>
		RandomAccessIterator _next(RandomAccessIterator it, typename iterator_traits<RandomAccessIterator>::difference_type n, ft::random_access_iterator_tag)
		{
			ft::advance(it, n);
			return it;
		}

	} // private namespace

	template <class Iterator>
	Iterator next(Iterator it,
						 typename iterator_traits<Iterator>::difference_type n = 1)
	{
		return _next(it, n, typename iterator_traits<Iterator>::iterator_category());
	}

} // namespace ft
