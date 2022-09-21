#pragma once

#include <memory>
#include "iterator/vector_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include "type_traits/type_traits.hpp"
#include "iterator/iterator_utils.hpp"
#include "algorithm/equal.hpp"
#include "algorithm/lexicographical_compare.hpp"
#include "algorithm/copy.hpp"
#include "algorithm/min.hpp"
#include <stdexcept>
#include <limits>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
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
		struct content
		{
			pointer start;
			pointer end;
		} _content;

		/* Private Functions */
	private:
		void _allocate_content(const size_type &n)
		{
			this->_content.end = this->_content.start = this->_alloc.allocate(n);
			this->_capacity = n;
		}

		void _fill_content(const value_type &val, const size_type &start = 0, const size_type *end = NULL)
		{
			if (end == NULL)
				end = &this->_capacity;
			for (size_type i = start; i < *end; ++i, ++this->_content.end)
			{
				this->_alloc.construct(this->_content.end, val);
			}
		}

		template < class Vector >
		void _fill_content(Vector &vc,
						   typename ft::enable_if<!ft::is_integral<Vector>::value, bool>::type = true)
		{
			for (size_type i = 0; i < vc.size(); ++i)
			{
				this->_alloc.construct(this->_content.end, vc[ i ]);
				++this->_content.end;
			}
		}

		template < class InputIterator >
		void _fill_content(InputIterator first, InputIterator last,
						   typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		{
			for (size_type n = 0; n < this->capacity() && first != last; ++n, ++first)
			{
				this->_alloc.construct(this->_content.end, *first);
				++this->_content.end;
			}
		}

		void _destroy(pointer start, pointer end)
		{
			for (pointer i = start; i != end; ++i)
			{
				this->_alloc.destroy(i);
			}
		}

		void _copy_assign_alloc(const vector &x)
		{
			if (this->_alloc != x._alloc)
			{
				this->clear();
				this->_alloc.deallocate(this->_content.start, this->_capacity);
				this->_content.start = this->_content.end = NULL;
			}
			this->_alloc = x._alloc;
		}

		/* Constructors */
	public:
		/* Default Constructor */
		explicit vector(const allocator_type &alloc = allocator_type()) : _capacity(), _alloc(alloc), _content() { }

		/* Fill Constructor */
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _capacity(n), _alloc(alloc)
		{
			this->_allocate_content(this->_capacity);
			this->_fill_content(val);
		}

		/* Range Constructor */
		template < class InputIterator >
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) : _capacity(
				size_type()), _alloc(alloc), _content()
		{
			this->clear();
			for (InputIterator iter = first; iter != last; ++iter)
			{
				this->push_back(*iter);
			}
		}

		/* Copy Constructor */
		vector(const vector &x) : _capacity(x.capacity()), _alloc(x.get_allocator()), _content()
		{
			this->_allocate_content(this->_capacity);
			this->_fill_content(x);
		}

		/* Destructors */
	public:
		~vector()
		{
			if (this->_content.start)
			{
				this->clear();
				this->_alloc.deallocate(this->_content.start, this->_capacity);
			}
		}

		/* Public Member Functions */
	public:
		vector &operator=(const vector &x)
		{
			if (this == &x)
				return *this;

			this->_copy_assign_alloc(x);
			this->assign(x.begin(), x.end());
			return *this;
		}

		/* Iterator functions */
	public:
		iterator begin() { return iterator(this->_content.start); }

		const_iterator begin() const { return const_iterator(this->_content.start); }

		iterator end() { return iterator(this->_content.end); }

		const_iterator end() const { return const_iterator(this->_content.end); }

		reverse_iterator rbegin() { return reverse_iterator(this->end()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

		reverse_iterator rend() { return reverse_iterator(this->begin()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		/* Capacity functions */
	public:
		size_type size() const { return ft::distance(this->begin(), this->end()); }

		size_type max_size() const
		{
			return ft::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max());
		}

		size_type capacity() const { return this->_capacity; }

		bool empty() const { return this->size() == 0; }

		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::length_error("ft::vector::resize");
			if (n < this->size())
			{
				_destroy(this->_content.start + n, this->_content.end);
				this->_content.end = this->_content.start + n;
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
			const size_type old_capacity = this->capacity();
			const content old_content = { this->_content.start, this->_content.end };
			// allocate new space
			this->_allocate_content(n);
			// copy old stuff into new space
			this->_fill_content(iterator(old_content.start), iterator(old_content.end));
			// destroy old stuff
			_destroy(old_content.start, old_content.end);
			if (old_content.start != NULL)
				this->_alloc.deallocate(old_content.start, old_capacity);

			this->_capacity = n;
		}

		/* Element access functions */
	public:
		reference operator[](size_type n) { return *(this->_content.start + n); }

		const_reference operator[](size_type n) const { return *(this->_content.start + n); }

		reference at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("ft::vector::at");
			return *(this->_content.start + n);
		}

		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("ft::vector::at");
			return *(this->_content.start + n);
		}

		reference front() { return *(this->_content.start); }

		const_reference front() const { return *(this->_content.start); }

		reference back() { return *(this->_content.end - 1); }

		const_reference back() const { return *(this->_content.end - 1); }

		/* Modifiers functions */
	public:
		template < class InputIterator >
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		{
			this->clear();
			for (InputIterator iter = first; iter != last; ++iter)
				this->push_back(*iter);
		}

		void assign(size_type n, const value_type &val)
		{
			const size_type new_size = n;

			_destroy(this->_content.start, this->_content.end);
			if (new_size > this->_capacity)
			{
				if (this->_content.start != NULL)
					this->_alloc.deallocate(this->_content.start, this->_capacity);
				this->_allocate_content(new_size);
			}

			this->_content.end = this->_content.start;
			this->_fill_content(val, 0, &new_size);
		}

		void push_back(const value_type &val)
		{
			this->resize(this->size() + 1, val);
		}

		void pop_back()
		{
			--this->_content.end;
			this->_alloc.destroy(this->_content.end);
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type dist = ft::distance(this->begin(), position);
			insert(position, 1, val);
			return iterator(this->_content.start + dist);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return;

			if (this->size() + n > this->capacity())
			{
				// copy old stuff
				const size_type old_cap = this->capacity();
				const content old_content = { this->_content.start, this->_content.end };
				iterator old_start = this->begin();
				iterator old_end = this->end();
				// reallocate to capacity + n
				this->_allocate_content(old_cap + n);
				// write old stuff to content until position - 1
				this->_fill_content(old_start, position);
				// write val n times
				this->_fill_content(val, 0, &n);
				// continue writing old stuff to content until cap
				this->_fill_content(position, old_end);
				// destroy old stuff
				_destroy(old_content.start, old_content.end);
				if (old_content.start != NULL)
					this->_alloc.deallocate(old_content.start, old_cap);
			}
			else
			{
				for (iterator end = this->end() - 1; end != position - 1; --end, ++this->_content.end)
				{
					iterator tmp = end + n;
					*tmp = *end;
					*end = val;
				}
			}
		}

		template < class InputIterator >
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		{
			vector vc(first, last);
			const size_type n = vc.size();

			if (n == 0)
				return;

			if (this->size() + n > this->capacity())
			{
				// copy old stuff
				const size_type old_cap = this->capacity();
				const content old_content = { this->_content.start, this->_content.end };
				iterator old_start = this->begin();
				iterator old_end = this->end();
				// reallocate to capacity + n
				this->_allocate_content(old_cap + n);
				// write old stuff to vector
				this->_fill_content(old_start, position);
				// write range to vector
				this->_fill_content(vc);
				// continue writing old stuff to content until cap
				this->_fill_content(position, old_end);
				// destroy old stuff
				_destroy(old_content.start, old_content.end);
				if (old_content.start != NULL)
					this->_alloc.deallocate(old_content.start, old_cap);
			}
			else
			{
				for (iterator end = this->end() - 1; end != position - 1; --end, ++this->_content.end)
				{
					iterator tmp = end + n;
					*tmp = *end;
					*end = *(vc.begin());
					vc.erase(vc.begin());
				}
			}
		}

		iterator erase(iterator position) { return erase(position, position + 1); }

		iterator erase(iterator first, iterator last)
		{
			iterator last_elem_added = ft::copy(last, this->end(), first);
			for (pointer p = this->_content.start + ft::distance(this->begin(), last_elem_added);
				 p != this->_content.end; ++p)
			{
				this->_alloc.destroy(p);
			}
			this->_content.end -= ft::distance(first, last);
			return first;
		}

		void swap(vector &x)
		{
			// copy stuff from x
			const content x_content_copy = { x._content.start, x._content.end };
			const size_type x_capacity = x._capacity;
			// swap addresses from x with addresses of this
			x._content.start = this->_content.start;
			x._content.end = this->_content.end;
			// swap capacity
			x._capacity = this->_capacity;
			// swap addresses of this with addresses of x
			this->_content.start = x_content_copy.start;
			this->_content.end = x_content_copy.end;
			// swap capacity
			this->_capacity = x_capacity;
		}

		void clear()
		{
			this->erase(this->begin(), this->end());
			this->_content.end = this->_content.start;
		}

		/* Allocator functions */
	public:
		allocator_type get_allocator() const { return this->_alloc; }
	};

	/* Relational Operators Overload */
	template < class T, class Alloc >
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template < class T, class Alloc >
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }

	template < class T, class Alloc >
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template < class T, class Alloc >
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(rhs < lhs); }

	template < class T, class Alloc >
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return rhs < lhs; }

	template < class T, class Alloc >
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }

	/* Swap */
	template < class T, class Alloc >
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { return x.swap(y); }

} // namespace ft
