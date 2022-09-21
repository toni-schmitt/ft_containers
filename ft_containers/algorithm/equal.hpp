#pragma once

namespace ft
{
	/* Equal */
	template < class InputIterator1, class InputIterator2 >
	bool equal(InputIterator1 first_1, InputIterator1 last_1, InputIterator2 first_2)
	{
		while (first_1 != last_1)
		{
			if (!(*first_1 == *first_2))
				return false;
			++first_1;
			++first_2;
		}
		return true;
	}

	/* Predicate */
	template < class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool equal(InputIterator1 first_1, InputIterator1 last_1, InputIterator2 first_2, BinaryPredicate pred)
	{
		while (first_1 != last_1)
		{
			if (!pred(*first_1, *first_2))
				return false;
			++first_1;
			++first_2;
		}
		return true;
	}

} // namespace ft
