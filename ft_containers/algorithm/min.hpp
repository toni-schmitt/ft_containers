#pragma once

#include <algorithm>

namespace ft
{
	template <class T, class Compare>
	const T &min(const T &a, const T &b, Compare comp)
	{
		return comp(b, a) ? b : a;
	}

	template <class T>
	const T &min(const T &a, const T &b)
	{
		return ft::min<T, std::less<T> >(a, b, std::less<T>());
	}
} // namespace ft
