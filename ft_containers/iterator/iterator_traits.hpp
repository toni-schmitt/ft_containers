#pragma once

#include <cstddef>
#include <iterator>

namespace ft
{
	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

	template < class Iterator >
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template < class T >
	class iterator_traits<T *>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template < class T >
	class iterator_traits<const T *>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

} // namespace ft
