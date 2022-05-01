#pragma once

namespace ft
{
	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		while (first != last)
		{
			*result = *first;
			++result;
			++first;
		}
		return result;
	}
} // namespace ft
