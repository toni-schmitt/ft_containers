#pragma once

#include <memory>
#include "ft_iterator/ft_random_access_iterator.hpp"
#include "ft_iterator/ft_reverse_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
#pragma region Member Types
		/* Member Types */
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
#pragma endregion

#pragma region Private Members
		/* Private Members */

		size_type _capacity;
		allocator_type _alloc;

#pragma endregion

#pragma region Constructors
		/* Constructors */
		explicit vector(const allocator_type &alloc = allocator_type());
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		vector(const vector &x);
#pragma endregion

#pragma region Destructors
		/* Destructors */
		~vector();
#pragma endregion

#pragma region Public Member Functions
		/* Public Member Functions */

#pragma region Iterators
		/* Iterator functions */

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

#pragma endregion

#pragma region Capacity
		/* Capacity functions */

		size_type size() const;
		size_type max_size() const { return this->_alloc.max_size(); }
		size_type capacity() const { return this->_capacity; }

		bool empty() const;

		void resize(size_type n, value_type val = value_type());

		void reserve(size_type n);

#pragma endregion

#pragma region Element access
		/* Element access functions */

		reference operator[](size_type n);
		const_reference operator[](size_type n) const;

		reference at(size_type n);
		const_reference at(size_type n) const;

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

#pragma endregion

#pragma region Modifiers
		/* Modifiers functions */

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type &val);

		void push_back(const value_type &val);
		void pop_back();

		iterator insert(iterator position, const value_type &val);
		void insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void swap(vector &x);

		void clear();

#pragma endregion

#pragma region Allocator
		/* Allocator functions */

		allocator_type get_allocator() const;

#pragma endregion

#pragma endregion
	};

#pragma region Non member function overloads

	/* Relational Operators Overload */
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	/* Swap */
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);

#pragma endregion
} // namespace ft
