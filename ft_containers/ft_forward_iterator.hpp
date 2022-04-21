#pragma once

#include <iterator>
#include <stddef.h>

namespace ft
{
	template <class T>
	class forward_iterator
	{
		/* Iterator Tags ( == Member Types? ) */
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference = &value_type;
		using const_reference = const & value_type;
		using pointer = *value_type;
		using const_pointer = const * value_type;

		/* Constructors: */
		forward_iterator() : _ptr(NULL);
		forward_iterator(pointer ptr) : _ptr(ptr);
		forward_iterator(const forward_iterator &cpy) : _ptr(cpy._ptr);

		/* Destructors: */
		~forward_iterator();

		/* Overloaded Operators */
		forward_iterator &operator=(const forward_iterator &sec)
		{
			if (this == &sec)
				return *this;

			this->_ptr = sec._ptr;

			return *this;
		};

		/* Derefernece Operators */
		reference operator*() const { return *this->_ptr; }
		pointer operator->() const { return this->_ptr; }

		/* Increment Operators */
		forward_iterator &operator++()
		{
			this->_ptr++;
			return *this;
		}
		forward_iterator operator++(T)
		{
			forward_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		/* Comparison Operators */
		friend bool operator==(const forward_iterator &a, const forward_iterator &b) { return a._ptr == b._ptr; }
		friend bool operator!=(const forward_iterator &a, const forward_iterator &b) { return a._ptr != b._ptr; }

	protected:
		pointer _ptr;
	};
} // namespace ft
