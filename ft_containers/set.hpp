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

		/* Private Members */
	private:
		value_compare _comp;
		allocator_type _alloc;
		tree_type _rbt;

		/* Constructor */
	public:
		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(
				comp), _alloc(alloc) { }

		template < class InputIterator >
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc)
		{
			this->insert(first, last);
		}

		set(const set &x) : _comp(x._comp), _alloc(x._alloc), _rbt(x._rbt) { }

		/* Destructor */
	public:
		~set() { this->clear(); }

		/* Public Member Functions */
	public:
		set &operator=(const set &x)
		{
			if (this == &x)
				return *this;

			this->_rbt = x._rbt;
			this->_comp = x._comp;
			this->_alloc = x._alloc;

			return *this;
		}

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
		bool empty() const { return this->_rbt.empty(); }

		size_type size() const { return this->_rbt.size(); }

		size_type max_size() const { return this->_rbt.get_node_allocator().max_size(); }

		/* Modifiers */
	public:
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			iterator it = this->find(val);
			if (it != this->end())
				return ft::pair<iterator, bool>(it, false);
			return ft::pair<iterator, bool>(iterator(this->_rbt.insert(val)), true);
		}

		iterator insert(iterator position, const value_type &val)
		{
			( void ) position;
			iterator it = this->find(val);
			if (it != this->end())
				return it;
			return iterator(this->_rbt.insert(val));
		}

		template < class InputIterator >
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
			{
				if (this->find(*it) == this->end())
					this->_rbt.insert(*it);
			}
		}

		void erase(iterator position)
		{
			if (position == this->end())
				return;

			this->_rbt.erase(position.get_base_ptr());
		}

		size_type erase(const value_type &val)
		{
			iterator it = this->find(val);
			if (it == this->end())
				return 0;
			this->_rbt.erase(it.get_base_ptr());
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
		}

		void swap(set &x) { this->_rbt.swap(x._rbt); }

		void clear()
		{
			if (this->empty())
				return;
			this->_rbt.clear();
		}

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