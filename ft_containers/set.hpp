#pragma once

#include <memory>
#include "iterator/iterator_traits.hpp"
#include "iterator/reverse_iterator.hpp"
#include "utility/pair.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		/* Member Types */
	public:
		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::bidirectional_iterator<value_type, set> iterator;
		typedef ft::bidirectional_iterator<const value_type, set> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

		/* Constructor */
	public:
		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) { }

		template < class InputIterator >
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
		{

		}

		set(const set &x) { }

		/* Destructor */
	public:
		~set() { }

		/* Public Member Functions */
	public:
		set &operator=(const set &x) { }

		/* Iterator Functions */
	public:
		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		reverse_iterator rbegin();

		const_reverse_iterator rbegin() const;

		reverse_iterator rend();

		const_reverse_iterator rend() const;

		/* Capacity Functions */
	public:
		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		/* Modifiers */
	public:
		ft::pair<iterator, bool> insert(const value_type &val);

		iterator insert(iterator position, const value_type &val);

		template < class InputIterator >
		void insert(InputIterator first, InputIterator last);

		void erase(iterator position);

		size_type erase(const value_type &val);

		void erase(iterator first, iterator last);

		void swap(set &x);

		void clear();

		/* Observers */
	public:
		key_compare key_comp() const;

		value_compare value_comp() const;

		/* Operations */
	public:
		iterator find(const value_type &val) const;

		size_type count(const value_type &val) const;

		iterator lower_bound(const value_type &val) const;

		iterator upper_bound(const value_type &val) const;

		ft::pair<iterator, iterator> equal_range(const value_type &val) const;

		/* Allocator Functions */
	public:
		allocator_type get_allocator() const;

	};
};