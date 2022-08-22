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
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::pointer pointer;
		typedef typename container_type::const_pointer const_pointer;

		/* Private Members */
	private:
		container_type _container;

		/* Constructors */
	public:
		explicit stack(const container_type &ctnr = container_type()) : _container(ctnr) {}

		/* Public Member functions */

		/* Capacity functions */
	public:
		bool empty() const { return this->_container.empty(); }

		size_type size() const { return this->_container.size(); }

		/* Element access functions */
	public:
		value_type &top() { return this->_container.back(); }
		const value_type &top() const { return this->_container.back(); }

		/* Modifiers functions */
	public:
		void push(const value_type &val) { this->_container.push_back(val); }

		void pop() { this->_container.pop_back(); }

		/* Friend declarations */
	public:
		template <class Type, class C>
		friend bool operator==(const stack<Type, C> &lhs, const stack<Type, C> &rhs);

		template <class Type, class C>
		friend bool operator!=(const stack<Type, C> &lhs, const stack<Type, C> &rhs);

		template <class Type, class C>
		friend bool operator<(const stack<Type, C> &lhs, const stack<Type, C> &rhs);

		template <class Type, class C>
		friend bool operator<=(const stack<Type, C> &lhs, const stack<Type, C> &rhs);

		template <class Type, class C>
		friend bool operator>(const stack<Type, C> &lhs, const stack<Type, C> &rhs);

		template <class Type, class C>
		friend bool operator>=(const stack<Type, C> &lhs, const stack<Type, C> &rhs);
	};

	/* Non-member function overloads */

	/* Relational operators */
	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._container == rhs._container; }

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._container != rhs._container; }

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._container < rhs._container; }

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._container <= rhs._container; }

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._container > rhs._container; }

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs._container >= rhs._container; }
} // namespace ft
