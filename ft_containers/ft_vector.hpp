#pragma once

#include <memory>
#include "ft_iterator/ft_random_access_iterator.hpp"
#include "ft_iterator/ft_reverse_iterator.hpp"
#include "ft_type_traits/ft_type_traits.hpp"
#include "ft_iterator/ft_iterator_utils.hpp"
#include "ft_algorithm/ft_equal.hpp"
#include "ft_algorithm/ft_lexicographical_compare.hpp"
#include "ft_algorithm/ft_copy.hpp"
#include <stdexcept>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		/* Member Types */
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type, vector> iterator;
		typedef ft::random_access_iterator<const value_type, vector> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		/* Private Members */
	private:
		size_type _capacity;
		allocator_type _alloc;
		struct Content
		{
			pointer _start;
			pointer _end;
		} _content;

		/* Private Functions */
	private:
		void _allocate_content(const size_type &n)
		{
			this->_content._end = this->_content._start = this->_alloc.allocate(n);
			this->_capacity = n;
		}

		void _fill_content(const value_type &val, const size_type &start = 0, const size_type *end = NULL)
		{
			if (end == NULL)
				end = &this->_capacity;
			for (size_type i = start; i < *end; ++i)
			{
				this->_alloc.construct(this->_content._end, val);
				++this->_content._end;
			}
		}

		void _fill_content(const vector &arr, const size_type &start = 0, const size_type *end = NULL)
		{
			if (end == NULL)
				end = &this->_capacity;
			for (size_type i = start; i < *end && i < arr.capacity(); ++i)
			{
				this->_alloc.construct(this->_content._end, arr[i]);
				++this->_content._end;
			}
		}

		template <class InputIterator>
		void _fill_content(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->_alloc.construct(this->_content._end, *first);
				++first;
				++this->_content._end;
			}
		}

		void _destroy_and_delete(pointer start, pointer end)
		{
			while (end != start)
			{
				this->_alloc.destroy(end);
				this->_alloc.deallocae(end, 1);
				--end;
			}
		}

		void _destroy(pointer start, pointer end)
		{
			while (end != start)
			{
				this->_alloc.destroy(end);
				--end;
			}
		}

		/* Constructors */
	public:
		/* Default Constructor */
		explicit vector(const allocator_type &alloc = allocator_type()) : _capacity(), _alloc(alloc), _content() {}

		/* Fill Constructor */
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _capacity(n), _alloc(alloc)
		{
			this->_allocate_content(this->_capacity);
			this->_fill_content(val);
		}

		/* Range Constructor */
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) : _capacity(ft::distance(first, last)), _alloc(alloc), _content()
		{
			this->_allocate_content(this->capacity);
			this->_fill_content(first, last);
		}

		/* Copy Constructor */
		vector(const vector &x) : _capacity(x.capacity()), _alloc(x.get_allocator()), _content()
		{
			this->_allocate_content(this->capacity);
			this->_fill_content(x);
		}

		/* Destructors */
	public:
		~vector()
		{
			if (this->_content._start)
			{
				this->clear();
				this->_alloc.deallocate(this->_content._start, this->_capacity);
			}
		}

		/* Public Member Functions */

		/* Iterator functions */
	public:
		iterator begin() { return iterator(this->_content._start); }
		const_iterator begin() const { return const_iterator(this->_content._start); }

		iterator end() { return iterator(this->_content._end); }
		const_iterator end() const { return const_iterator(this->_content._end); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(begin()); }

		/* Capacity functions */
	public:
		size_type size() const { return ft::distance(this->begin(), this->end()); }
		size_type max_size() const { return this->_alloc.max_size(); }
		size_type capacity() const { return this->_capacity; }

		bool empty() const { return this->size() == 0; }

		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::length_error("ft::vector::resize");
			if (n < this->size())
			{
				_destroy(this->_content._start + n, this->_content._end);
				this->_content._end = this->_content._start + n;
				return;
			}

			if (n > this->_capacity)
			{
				if (n <= this->_capacity * 2)
					this->reserve(this->_capacity * 2);
				else
					this->reserve(n);
			}
			this->_fill_content(val, this->size(), &n);
		}

		void reserve(size_type n)
		{
			if (n <= this->_capacity)
				return;
			if (n > this->max_size())
				throw std::length_error("ft::vector::reserve");

			// copy old stuff
			const size_type old_size = this->size();
			const Content old_content = {this->_content._start, this->_content._end};
			// allocate new space
			this->_allocate_content(n);
			// copy old stuff into new space
			this->_fill_content(iterator(old_content._start), iterator(old_content._end));
			// destroy old stuff
			_destroy(old_content._start, old_content._end);
			this->_alloc.deallocate(old_content._start, old_size);

			this->_capacity = n;
		}

		/* Element access functions */
	public:
		reference operator[](size_type n) { return *(this->_content._start + n); }
		const_reference operator[](size_type n) const { return *(this->_content._start + n); }

		reference at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("ft::vector::at");
			return *(this->_content._start + n);
		}
		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("ft::vector::at");
			return *(this->_content._start + n);
		}

		reference front() { return *(this->_content._start); }
		const_reference front() const { return *(this->_content._start); }

		reference back() { return *(this->_content._end - 1); }
		const_reference back() const { return *(this->_content._end - 1); }

		/* Modifiers functions */
	public:
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			const size_type new_size = ft::distance(first, last);

			_destroy(this->_content._start, this->_content._end);
			if (new_size > this->_capacity)
				this->_allocate_content(new_size);

			this->_content._end = this->_content._start;
			this->_fill_content(first, last);
		}
		void assign(size_type n, const value_type &val)
		{
			const size_type new_size = n;

			_destroy(this->_content._start, this->_content._end);
			if (new_size > this->_capacity)
				this->_allocate_content(new_size);

			this->_content._end = this->_content._start;
			this->_fill_content(val);
		}

		void push_back(const value_type &val)
		{
			this->resize(this->size() + 1, val);
		}
		void pop_back()
		{
			--this->_content._end;
			this->_alloc.destroy(this->_content._end);
		}

		iterator insert(iterator position, const value_type &val)
		{
			insert(position, 1, val);
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (this->size() + n > this->capacity())
			{
				// copy old stuff
				const size_type old_cap = this->capacity();
				const Content old_content = {this->_content._start, this->_content._end};
				iterator old_start = this->begin();
				iterator old_end = this->end();
				// reallocate to capacity + n
				this->_allocate_content(old_cap + n);
				// write old stuff to content until position - 1
				this->_fill_content(old_start, position - 1);
				// write val n times
				this->_fill_content(val, 0, &n);
				// continue writing old stuff to content until cap
				this->_fill_content(position, old_end);
				// destroy old stuff
				_destroy(old_content._start, old_content._end);
				this->_alloc.deallocate(old_content._start, old_cap);
			}
			else
			{
				for (iterator end = this->end() - 1; end != position - 1; --end, ++this->_content._end)
				{
					iterator tmp = end + n;
					*tmp = *end;
					*end = val;
				}
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		{
			const size_type n = ft::distance(first, last);
			if (this->size() + ft::distance(first, last) > this->capacity())
			{
				// copy old stuff
				const size_type old_cap = this->capacity();
				const Content old_content = {this->_content._start, this->_content._end};
				iterator old_start = this->begin();
				iterator old_end = this->end();
				// reallocate to capacity + n
				this->_allocate_content(old_cap + n);
				// write old stuff to content until position - 1
				this->_fill_content(old_start, position - 1);
				// write val n times
				this->_fill_content(first, last);
				// continue writing old stuff to content until cap
				this->_fill_content(position, old_end);
				// destroy old stuff
				_destroy(old_content._start, old_content._end);
				this->_alloc.deallocate(old_content._start, old_cap);
			}
			else
			{
				for (iterator end = this->end() - 1; end != position - 1; --end, ++this->_content._end)
				{
					iterator tmp = end + n;
					*tmp = *end;
					*end = *first;
					++first;
				}
			}
		}

		iterator erase(iterator position) { return erase(position, position + 1); }
		iterator erase(iterator first, iterator last)
		{
			iterator last_elem_added = ft::copy(last, this->end(), first);
			for (pointer p = this->_content._start + ft::distance(this->begin(), last_elem_added); p != this->_content._end; ++p)
			{
				this->_alloc.destroy(p);
			}
			this->_content._end -= ft::distance(first, last);
			return first;
		}

		void swap(vector &x);

		void clear()
		{
			_destroy(this->_content._start, this->_content._end);
		}

		/* Allocator functions */
	public:
		allocator_type get_allocator() const { return this->_alloc; }
	};

	/* Relational Operators Overload */
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(rhs < lhs); }

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return rhs < lhs; }

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }

	/* Swap */
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { return x.swap(y); }

} // namespace ft
