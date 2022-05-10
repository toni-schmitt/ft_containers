#pragma once

#include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		/* Member Types */
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef typename container_type::size_type size_type;

		/* Private Members */
	private:
		container_type _container;

		/* Constructors */
	public:
		explicit stack(const container_type &ctnr = container_type()) : _container(ctnr) {}

		/* Public Member functions */

		/* Capacity functions */
	public:
		bool empty() const;

		size_type size() const;

		/* Element access functions */
	public:
		value_type &top();
		const value_type &top() const;

		/* Modifiers functions */
	public:
		void push(const value_type &val);

		void pop();
	};

	/* Non-member function overloads */

	/* Relational operators */
	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
} // namespace ft
