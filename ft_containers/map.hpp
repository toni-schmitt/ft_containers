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
		/* Forward Declarations */
	public:
		class value_compare;

		/* Member Types */
	private:
		typedef map<Key, T, Compare, Alloc> map_type;
	public:
		/* Value Types */
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

		public:
			value_compare() : comp() { }

			explicit value_compare(Compare c) : comp(c) { }

			/* Public Member functions */
		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return this->comp(x.first, y.first);
			}
		};

		/* Private Member */
	private:
		value_compare _compare;
		allocator_type _alloc;
		tree_type _rbt;

		/* Constructors */
	public:
		/* Default Constructor */
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _compare(comp), _alloc(alloc) { }

		/* Range Constructor */
		template < class InputIterator >
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _compare(comp), _alloc(alloc)
		{
			this->insert(first, last);
		}

		/* Copy Constructor */
		map(const map &x) : _compare(x._compare), _alloc(x._alloc), _rbt(x._rbt) { }

		/* Destructors */
	public:
		~map()
		{
			this->_rbt.clear();
		}

		/* Public Member Functions */
	public:
		map &operator=(const map &x)
		{
			if (&x == this)
				return *this;

			this->_rbt = x._rbt;

			return *this;
		}

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
		bool empty() const { return this->_rbt.empty(); }

		size_type size() const { return this->_rbt.size(); }

		size_type max_size() const { return this->_rbt.get_node_allocator().max_size(); }

		/* Element access functions */
	public:
		mapped_type &operator[](const key_type &k)
		{
			iterator it = this->find(k);
			if (it == this->end())
				return insert(ft::pair<key_type, mapped_type>(k, mapped_type())).first->second;
			return it->second;
		}

		mapped_type &at(const key_type &k)
		{
			iterator it = this->find(k);
			if (it == this->end())
				throw std::out_of_range("Out of range");
			return it->second;
		}

		const mapped_type &at(const key_type &k) const
		{
			const_iterator it = this->find(k);
			if (it == this->end())
				throw std::out_of_range("Out of range");
			return it->second;
		}

		/* Modifiers functions */
	public:
		/* Insert functions */
		/* Insert Single Element */
		pair<iterator, bool> insert(const value_type &val)
		{
			iterator x = find(val.first);
			if (x == this->end())
				return ft::pair<iterator, bool>(x, false);
			return ft::pair<iterator, bool>(iterator(this->_rbt.insert(val)), true);
		}

		/* Insert With Hint */
		iterator insert(iterator position, const value_type &val)
		{
			( void ) position; // we dont take hints here :D
			iterator x = this->find(val.first());
			if (x == this->end())
				return x;
			return iterator(this->_rbt.insert(val));
		}

		/* Insert Range */
		template < class InputIterator >
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
			{
				iterator x = this->find((*it).first);
				if (x == this->end())
					this->_rbt.insert(*it);
			}
		}

		/* Erase functions */
		void erase(iterator position)
		{
			if (position == this->end())
				return;
			this->_rbt.erase(position.base());
		}

		size_type erase(const key_type &k)
		{
			iterator it = this->find(k);
			if (it == this->end())
				return 0;
			this->_rbt.erase(it.base());
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			this->_rbt.erase(first.base(), last.base());
		}

		/* Swap function */
		void swap(map &x) { this->_rbt.swap(x._rbt); }

		/* Clear function */
		void clear() { this->_rbt.clear(); }

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
