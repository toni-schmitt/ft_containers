#pragma once

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
		pair();

		/* Copy Constructor */
		template < class U, class V >
		pair(const pair<U, V> &pr);

		/* Initialization Constructor */
		pair(const first_type &a, const second_type &b);

		/* Public Member Functions */
	public:
		pair &operator=(const pair &pr);
	};

	/* Non-member function overloads */

	/* Relational Operators */
	template < class T1, class T2 >
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

	template < class T1, class T2 >
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

	template < class T1, class T2 >
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

	template < class T1, class T2 >
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

	template < class T1, class T2 >
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

	template < class T1, class T2 >
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

} // namespace ft
