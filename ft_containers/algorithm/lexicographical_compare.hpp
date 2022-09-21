#pragma once

namespace ft
{
	template < class InputIterator1, class InputIterator2 >
	bool lexicographical_compare(
			InputIterator1 first_1, InputIterator1 last_1, InputIterator2 first_2, InputIterator2 last_2
	)
	{
		while (first_1 != last_1)
		{
			if (first_2 == last_2 || *first_2 < *first_1)
				return false;
			else if (*first_1 < *first_2)
				return true;
			++first_1;
			++first_2;
		}
		return (first_2 != last_2);
	}

} // namespace ft
