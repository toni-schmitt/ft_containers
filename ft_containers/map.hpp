#pragma once

#include <functional>
#include <memory>
#include "utility/make_pair.hpp"
#include "utility/pair.hpp"
#include "iterator/map_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include "iterator/iterator_traits.hpp"
#include "red_black_tree/red_black_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		/* Member Types */
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		/* Tree Types */
		typedef ft::red_black_tree<value_type, map_type, value_compare, Alloc> tree_type;
		typedef typename tree_type::iterator tree_iterator;
		typedef typename tree_type::const_iterator tree_const_iterator;
		/* Iterator Types */
		typedef ft::bidirectional_iterator<value_type, map_type, tree_type> iterator;
		typedef ft::bidirectional_iterator<const value_type, map_type, tree_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		class value_compare
		{
			friend class map;

			/* Member Types */
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			/* Protected Members */
		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) { }

			/* Public Member functions */
		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return this->comp(x.first, y.first);
			}
		};

		/* Constructors */
	public:
		/* Default Constructor */
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());

		/* Range Constructor */
		template < class InputIterator >
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type());

		/* Copy Constructor */
		map(const map &x);

		/* Destructors */
	public:
		~map();

		/* Public Member Functions */
	public:
		map &operator=(const map &x);

		/* Iterator functions */
	public:
		iterator begin() { return iterator(this->_rbt.begin()); }

		const_iterator begin() const { return const_iterator(this->begin()); }

		iterator end() { return iterator(this->_rbt.end()); }

		const_iterator end() const { return const_iterator(this->_rbt.end()); }

		reverse_iterator rbegin() { return reverse_iterator(this->end()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

		reverse_iterator rend() { return reverse_iterator(this->begin()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		/* Capacity functions */
	public:
		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		/* Element access functions */
	public:
		mapped_type &operator[](const key_type &k);

		/* Modifiers functions */
	public:
		/* Insert functions */
		/* Insert Single Element */
		pair<iterator, bool> insert(const value_type &val);

		/* Insert With Hint */
		iterator insert(iterator position, const value_type &val);

		/* Insert Range */
		template < class InputIterator >
		void insert(InputIterator first, InputIterator last);

		/* Erase functions */
		void erase(iterator position);

		size_type erase(const key_type &k);

		void erase(iterator first, iterator last);

		/* Swap function */
		void swap(map &x);

		/* Clear function */
		void clear();

		/* Observer functions */
	public:
		key_compare key_comp() const;

		value_compare value_comp() const;

		/* Operation functions */
	public:
		iterator find(const key_type &k);

		const_iterator find(const key_type &k) const;

		size_type count(const key_type &k) const;

		iterator lower_bound(const key_type &k);

		const_iterator lower_bound(const key_type &k) const;

		iterator upper_bound(const key_type &k);

		const_iterator upper_bound(const key_type &k) const;

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

		pair<iterator, iterator> equal_range(const key_type &k);

		/* Allocator functions */
	public:
		allocator_type get_allocator() const;
	};
} // namespace ft
