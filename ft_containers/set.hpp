#pragma once

#include <memory>
#include "iterator/iterator_traits.hpp"
#include "iterator/reverse_iterator.hpp"
#include "utility/pair.hpp"
#include "red_black_tree/red_black_tree.hpp"
#include "algorithm/equal.hpp"
#include "algorithm/lexicographical_compare.hpp"

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
	private:
		typedef ft::red_black_tree<const value_type, value_compare, allocator_type> tree_type;
		typedef typename tree_type::iterator tree_iterator;
		typedef typename tree_type::const_iterator tree_const_iterator;
	public:
		typedef tree_const_iterator iterator;
		typedef tree_const_iterator const_iterator;
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
		iterator begin() { return iterator(this->_rbt.begin()); }

		const_iterator begin() const { return const_iterator(this->_rbt.begin()); }

		iterator end() { return iterator(this->_rbt.end()); }

		const_iterator end() const { return const_iterator(this->_rbt.end()); }

		reverse_iterator rbegin() { return reverse_iterator(this->_rbt.rbegin()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_rbt.rbegin()); }

		reverse_iterator rend() { return reverse_iterator(this->_rbt.rend()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(this->_rbt.rend()); }

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