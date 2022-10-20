#pragma once

#include <iostream>

namespace ft
{
	template < class T1, class T2 >
	struct pair
	{
		/* Member Types */
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		/* Public Members */
	public:
		first_type first;
		second_type second;

		/* Constructors */
	public:
		/* Default Constructor */
		pair() : first(), second() { }

		/* Copy Constructor */
		template < class U, class V >
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) { }

		/* Initialization Constructor */
		pair(const first_type &a, const second_type &b) : first(a), second(b) { }

		/* Public Member Functions */
	public:
		pair &operator=(const pair &pr)
		{
			if (this == &pr)
				return *this;

			this->first = pr.first;
			this->second = pr.second;

			return *this;
		}
	};

	/* Non-member function overloads */

	template < class T1, class T2 >
	std::ostream &operator<<(std::ostream &os, const ft::pair<T1, T2> &pair)
	{
		os << pair.first << " " << pair.second;
		return os;
	}

	/* Relational Operators */
	template < class T1, class T2 >
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T1, class T2 >
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs == rhs); }

	template < class T1, class T2 >
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template < class T1, class T2 >
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first <= rhs.first || (!(rhs.first <= lhs.first) && lhs.second <= rhs.second));
	}

	template < class T1, class T2 >
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return (rhs < lhs); }

	template < class T1, class T2 >
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return (!(lhs <= rhs)); }


	template < class T1, class T2 >
	ft::pair<T1, T2> make_pair(T1 x, T2 y) { return ft::pair<T1, T2>(x, y); }

} // namespace ft
