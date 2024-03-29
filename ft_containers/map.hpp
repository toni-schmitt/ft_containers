#pragma once

#include <functional>
#include <memory>
#include "utility/pair.hpp"
//#include "iterator/map_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include "iterator/iterator_traits.hpp"
#include "red_black_tree/red_black_tree.hpp"
#include "algorithm/equal.hpp"
#include "algorithm/lexicographical_compare.hpp"

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
		typedef ft::red_black_tree<value_type, value_compare, Alloc> tree_type;
		typedef typename tree_type::iterator tree_iterator;
		typedef typename tree_type::const_iterator tree_const_iterator;
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

	public:
		typedef class map_iterator
		{
		public:
			typedef bidirectional_iterator_tag iterator_category;
			typedef typename tree_iterator::value_type value_type;
			typedef typename tree_iterator::difference_type difference_type;
			typedef typename tree_iterator::reference reference;
			typedef typename tree_iterator::pointer pointer;

		protected:
			tree_iterator _tree_ite;

		public:
			map_iterator() : _tree_ite() { }

			explicit map_iterator(const tree_iterator &tree_ite) : _tree_ite(tree_ite) { }

			map_iterator(const map_iterator &other) : _tree_ite(other._tree_ite) { }

			tree_iterator base() const { return _tree_ite; }

			tree_iterator get_tree_ite() const { return (_tree_ite); }

			map_iterator &operator=(const map_iterator &other)
			{
				_tree_ite = other._tree_ite;
				return (*this);
			}

			reference operator*() const { return (*_tree_ite); }

			pointer operator->() const { return (&(*_tree_ite)); }

			map_iterator &operator++()
			{
				++_tree_ite;
				return (*this);
			}

			map_iterator &operator--()
			{
				--_tree_ite;
				return (*this);
			}

			map_iterator operator++(int)
			{
				tree_iterator tmp = _tree_ite;
				++_tree_ite;
				return map_iterator(tmp);
			}

			map_iterator operator--(int)
			{
				tree_iterator tmp = _tree_ite;
				--_tree_ite;
				return map_iterator(tmp);
			}

			friend bool operator==(const map_iterator &lhs, const map_iterator &rhs)
			{
				return (lhs.get_tree_ite() == rhs.get_tree_ite());
			}

			friend bool operator!=(const map_iterator &lhs, const map_iterator &rhs)
			{
				return (!(lhs == rhs));
			}
		} iterator;

		typedef class map_const_iterator
		{
		public:
			typedef bidirectional_iterator_tag iterator_category;
			typedef typename tree_const_iterator::value_type value_type;
			typedef typename tree_const_iterator::difference_type difference_type;
			typedef typename tree_const_iterator::reference reference;
			typedef typename tree_const_iterator::pointer pointer;

		protected:
			iterator _nc_ite;

		public:
			map_const_iterator() : _nc_ite() { }

			map_const_iterator(const map_const_iterator &other) : _nc_ite(other._nc_ite) { }

			explicit map_const_iterator(const tree_const_iterator &const_tree_ite) : _nc_ite(
					iterator(const_tree_ite.get_base_ite())) { }

			explicit map_const_iterator(const tree_iterator &tree_ite) : _nc_ite(iterator(tree_ite)) { }

			map_const_iterator(const iterator &nc_ite) : _nc_ite(nc_ite) { }

			tree_const_iterator get_tree_ite() const { return tree_const_iterator(_nc_ite.get_tree_ite()); }

			map_const_iterator &operator=(const map_const_iterator &other)
			{
				_nc_ite = other._nc_ite;
				return (*this);
			}

			reference operator*() const { return ((_nc_ite.get_tree_ite()).get_base_ptr()->value); }

			pointer operator->() const { return (&(*_nc_ite)); }

			map_const_iterator &operator++()
			{
				++_nc_ite;
				return (*this);
			}

			map_const_iterator &operator--()
			{
				--_nc_ite;
				return (*this);
			}

			map_const_iterator operator++(int)
			{
				iterator tmp = _nc_ite;
				++_nc_ite;
				return map_const_iterator(tmp);
			}

			map_const_iterator operator--(int)
			{
				iterator tmp = _nc_ite;
				--_nc_ite;
				return map_const_iterator(tmp);
			}

			friend bool operator==(const map_const_iterator &lhs, const map_const_iterator &rhs)
			{
				return (lhs.get_tree_ite() == rhs.get_tree_ite());
			}

			friend bool operator!=(const map_const_iterator &lhs, const map_const_iterator &rhs)
			{
				return (!(lhs == rhs));
			}
		} const_iterator;


		/* Iterator Types */
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

		/* Private Member */
	private:
		value_compare _compare;
		allocator_type _alloc;
		tree_type _rbt;

		/* Constructors */
	public:
		/* Default Constructor */
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _compare(comp), _alloc(alloc), _rbt(tree_type()) { }

		/* Range Constructor */
		template < class InputIterator >
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _compare(comp), _alloc(alloc), _rbt(tree_type())
		{
			this->insert(first, last);
		}

		/* Copy Constructor */
		map(const map &x) : _compare(x._compare), _alloc(x._alloc), _rbt(x._rbt)
		{
			*this = x;
		}

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

			this->_rbt.clear();
			this->_rbt = x._rbt;

			return *this;
		}

		/* Iterator functions */
	public:
		iterator begin() { return iterator(this->_rbt.begin()); }

		const_iterator begin() const { return const_iterator(this->_rbt.begin()); }

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
			if (x != this->end())
				return ft::pair<iterator, bool>(x, false);
			return ft::pair<iterator, bool>(iterator(this->_rbt.insert(val)), true);
		}

		/* Insert With Hint */
		iterator insert(iterator position, const value_type &val)
		{
			( void ) position; // we dont take hints here :D
			iterator x = this->find(val.first);
			if (x != this->end())
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
		key_compare key_comp() const { return this->_compare.comp; }

		value_compare value_comp() const { return this->_compare; }

		/* Operation functions */
	public:
		/* Find */
	private:
		struct key_to_pair_equal
		{
			bool operator()(const key_type &key, const value_type &value) const
			{
				return key == value.first;
			}
		};

		struct key_to_pair_comp
		{
			bool operator()(const key_type &key, const value_type &value) const
			{
				return key_compare()(key, value.first);
			}
		};

	public:
		iterator find(const key_type &k)
		{

			if (this->empty())
				return this->end();
			return iterator(this->_rbt.search(k, key_to_pair_equal(), key_to_pair_comp()));
		}

		const_iterator find(const key_type &k) const
		{
			if (this->empty())
				return this->end();
			return const_iterator(this->_rbt.search(k, key_to_pair_equal(), key_to_pair_comp()));
		}

		size_type count(const key_type &k) const
		{
			const_iterator element = this->find(k);
			if (element == this->end())
				return 0;
			return 1;
		}

		iterator lower_bound(const key_type &k)
		{
			iterator x = this->find(k);
			if (x != this->end())
				return x;
			x = this->begin();
			for (iterator it = x; it != this->end() && x->first < k;)
			{
				++it;
				if (it->first > k)
					return it;
				x = it;
			}
			return x;
		}

		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator x = this->find(k);
			if (x != this->end())
				return x;
			x = this->begin();
			for (const_iterator it = x; it != this->end() && x->first < k;)
			{
				++it;
				if (it->first > k)
					return it;
				x = it;
			}
			return x;
		}

		iterator upper_bound(const key_type &k)
		{
			iterator it = this->begin();
			while (it != this->end())
			{
				if (it->first > k)
					break;
				++it;
			}
			return it;
		}

		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = this->begin();
			while (it != this->end())
			{
				if (it->first > k)
					break;
				++it;
			}
			return it;
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k));
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k));
		}

		/* Allocator functions */
	public:
		allocator_type get_allocator() const { return this->_alloc; }
	};

	/* Relational Operators Overload */
	template < class Key, class T, class Compare, class Alloc >
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return rhs < lhs; }

	template < class Key, class T, class Compare, class Alloc >
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}


	/* Swap */
	template < class Key, class T, class Compare, class Alloc >
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) { x.swap(y); }
} // namespace ft
