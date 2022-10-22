
#pragma once

#include "../iterator/iterator_traits.hpp"
#include <iostream>

namespace ft
{

	template < class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class red_black_tree
	{

		/* Forward Declarations */
	public:
		class rbt_iterator;

		class rbt_const_iterator;

	private:
		struct rbt_node;

		/* Member Types */
	public:
		typedef T value_type;
		typedef Compare value_compare;
		typedef Allocator value_allocator_type;
		typedef typename value_allocator_type::pointer pointer;
		typedef typename value_allocator_type::const_pointer const_pointer;
		typedef typename value_allocator_type::reference reference;
		typedef typename value_allocator_type::const_reference const_reference;
		typedef typename value_allocator_type::template rebind<rbt_node>::other node_allocator_type;
		typedef typename node_allocator_type::pointer node_pointer;
		typedef typename node_allocator_type::const_pointer const_node_pointer;
		typedef typename node_allocator_type::size_type size_type;
		typedef typename node_allocator_type::difference_type difference_type;
		typedef rbt_iterator iterator;
		typedef rbt_const_iterator const_iterator;
		typedef ft::reverse_iterator<rbt_iterator> reverse_iterator;
		typedef ft::reverse_iterator<rbt_const_iterator> const_reverse_iterator;

		/* Subclasses */
	private:
		/* Red Black Tree Node Struct */
		struct rbt_node
		{
			/* Public Members */
		public:
			rbt_node *parent;
			rbt_node *left;
			rbt_node *right;
			value_type value;
			bool is_black;

			/* Constructors */
		public:
			rbt_node() : parent(nil_node), left(nil_node), right(nil_node), value(value_type()), is_black(bool()) { }

			explicit rbt_node(bool is_black = false) : parent(nil_node), left(nil_node), right(nil_node),
													   value(value_type()),
													   is_black(is_black) { }

			explicit rbt_node(value_type val) : parent(nil_node), left(nil_node), right(nil_node), value(val),
												is_black(false) { }

			rbt_node(const rbt_node &other)
					: parent(nil_node), left(nil_node), right(nil_node), value(other.value), is_black(false) { }

			/* Public Member Functions */
		public:
			static void destroy(rbt_node *node) { delete node; }

		};

		/* Iterator Subclasses */
	public:

		friend class rb_iterator; // access to _NIL

		class rbt_iterator
		{
		public:
			typedef bidirectional_iterator_tag iterator_category;
			typedef typename red_black_tree::value_type value_type;
			typedef typename red_black_tree::difference_type difference_type;
			typedef typename red_black_tree::reference reference;
			typedef typename red_black_tree::pointer pointer;

		protected:
			node_pointer base_ptr;

		public:
			rbt_iterator() : base_ptr(nil_node) { }

			explicit rbt_iterator(const node_pointer &x) : base_ptr(x) { }

			rbt_iterator(const rbt_iterator &other) : base_ptr(other.base_ptr) { }

			node_pointer get_base_ptr() const { return (base_ptr); }

			reference operator*() const { return (base_ptr->value); }

			pointer operator->() const { return (&(operator*())); }

			rbt_iterator &operator++()
			{
				if (base_ptr != nil_node && base_ptr && base_ptr->right && base_ptr->right != nil_node)
					base_ptr = rb_min(base_ptr->right);
				else
				{
					node_pointer y = base_ptr->parent;
					while (y != nil_node && y->parent != NULL && base_ptr == y->right)
					{
						base_ptr = y;
						y = y->parent;
					}
					base_ptr = y;
				}
				return (*this);
			}

			rbt_iterator &operator--()
			{
				if (base_ptr != nil_node && base_ptr && base_ptr->left && base_ptr->left != nil_node)
					base_ptr = rb_max(base_ptr->left);
				else
				{

					node_pointer y = base_ptr->parent;
					while (y != nil_node && y->parent != NULL && y->parent != nil_node && base_ptr == y->left)
					{
						base_ptr = y;
						y = y->parent;
					}
					base_ptr = y;
				}
				return (*this);
			}

			rbt_iterator operator++(int)
			{
				node_pointer old = base_ptr;
				++*this;
				return (rbt_iterator(old));
			}

			rbt_iterator operator--(int)
			{
				node_pointer old = base_ptr;
				--*this;
				return (rbt_iterator(old));
			}

			friend bool operator==(const rbt_iterator &lhs, const rbt_iterator &rhs)
			{
				return (lhs.get_base_ptr() == rhs.get_base_ptr());
			}

			friend bool operator!=(const rbt_iterator &lhs, const rbt_iterator &rhs)
			{
				return (!(lhs == rhs));
			}
		};

		class rbt_const_iterator
		{
		public:
			typedef bidirectional_iterator_tag iterator_category;
			typedef typename red_black_tree::value_type value_type;
			typedef typename red_black_tree::difference_type difference_type;
			typedef typename red_black_tree::const_reference reference;
			typedef typename red_black_tree::const_pointer pointer;

		protected:
			rbt_iterator base_ite;

		public:
			rbt_const_iterator() : base_ite() { }

			explicit rbt_const_iterator(const node_pointer &x) : base_ite(rbt_iterator(x)) { }

			explicit rbt_const_iterator(const rbt_iterator &nc_it) : base_ite(nc_it) { }

			rbt_const_iterator(const rbt_const_iterator &other) : base_ite(other.base_ite) { }

			rbt_iterator get_base_ite() const { return (base_ite); }

			node_pointer get_base_ptr() const { return (base_ite.get_base_ptr()); }

			reference operator*() const { return (get_base_ptr()->value); }

			pointer operator->() const { return (&(operator*())); }

			rbt_const_iterator &operator++()
			{
				++base_ite;
				return (*this);
			}

			rbt_const_iterator &operator--()
			{
				--base_ite;
				return (*this);
			}

			rbt_const_iterator operator++(int)
			{
				node_pointer old = base_ite.get_base_ptr();
				++*this;
				return (rbt_const_iterator(old));
			}

			rbt_const_iterator operator--(int)
			{
				node_pointer old = base_ite.get_base_ptr();
				--*this;
				return (rbt_const_iterator(old));
			}

			friend bool operator==(const rbt_const_iterator &lhs, const rbt_const_iterator &rhs)
			{
				return (lhs.get_base_ptr() == rhs.get_base_ptr());
			}

			friend bool operator!=(const rbt_const_iterator &lhs, const rbt_const_iterator &rhs)
			{
				return (!(lhs == rhs));
			}
		};


		/* Protected Members */
	protected:
		static node_allocator_type node_allocator;
		static value_allocator_type value_allocator;
		static node_pointer nil_node;
		/* Private Members */
	private:
		static size_type _nb_trees;
		node_pointer _end_node;
		node_pointer _root;
		size_type _size;
		value_compare _comp;

		/* Constructors */
	public:
		red_black_tree() : _end_node(_new_node(false)), _size(0)
		{
			this->_end_node->left = nil_node;
			++this->_nb_trees;
		}

		red_black_tree(const Compare &c, const Allocator &alloc = Allocator()) : _root(nil_node), _size(0), _comp(c)
		{
			this->value_allocator = alloc;
			this->_end_node->left = nil_node;
			++this->_nb_trees;
		}

		red_black_tree(const red_black_tree &other) : _end_node(_new_node(false)), _size(0), _comp(other._comp)
		{
			this->_end_node->left = nil_node;
			++this->_nb_trees;
			for (const_iterator it = other.begin(); it != other.end(); it++)
				this->insert(*it);
		}

		/* Destructors */
	public:
		virtual ~red_black_tree()
		{
			if (!this->empty())
				this->_clear(this->_root);
			rbt_node::destroy(this->_end_node);
			--this->_nb_trees;
		}

		/* Public Member Functions */
	public:
		red_black_tree &operator=(const red_black_tree &other)
		{
			if (this == &other)
				return *this;

			this->clear();
			for (const_iterator it = other.begin(); it != other.end(); it++)
			{
				this->insert(*it);
			}
			return *this;
		}

		/**
		 * Prints the Tree to 'os'
		 * @param os ostream to print tree to ( default std::cout )
		 */
		void print_tree(std::ostream &os = std::cout) const
		{
			this->_pretty_print("", this->_end_node->left, false, -1, os);
			std::cout << std::endl;
		}

		/* Iterator Functions */
	public:
		iterator begin() { return this->empty() ? this->end() : iterator(this->min()); }

		iterator end() { return iterator(this->_end_node); }

		const_iterator begin() const { return this->empty() ? this->end() : const_iterator(this->min()); }

		const_iterator end() const { return const_iterator(this->_end_node); }

		reverse_iterator rbegin() { return reverse_iterator(this->end()); }

		reverse_iterator rend() { return reverse_iterator(this->begin()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		/* Capacity Functions */
	public:
		bool empty() const { return this->_size == 0; }

		size_type size() const { return this->_size; }

		node_pointer min() const { return this->empty() ? this->_end_node : rb_min(this->_root); }

		node_pointer max() const { return this->empty() ? this->_end_node : rb_max(this->_root); }

		/* Element Access Functions */
	public:

		/* Modifiers Functions */
	public:
		/* Insert Function */
		iterator insert(value_type value)
		{
			node_pointer x = this->_new_node(value);
			this->_tree_insert(x);
			++this->_size;
			this->_end_node->left = this->_root;
			this->_root->parent = this->_end_node;
			return iterator(x);
		}

		/* Erase Functions */
		void erase(node_pointer z)
		{
			if (!z || z == nil_node || z == this->_end_node)
				return;
			node_pointer tmp = z;
			this->_tree_delete(z);
			rbt_node::destroy(tmp);
		}

		void erase(iterator first, iterator last)
		{
			iterator it = first;
			while (it != last)
			{
				node_pointer z = it.get_base_ptr();
				node_pointer tmp = z;
				++it;
				if (!z || z == nil_node || z == this->_end_node)
					break;
				this->_tree_delete(z);
				rbt_node::destroy(tmp);
			}
		}

		void erase(const_reference value)
		{
			node_pointer z = this->search(value);
			this->erase(z);
		}

		void erase(iterator pos)
		{
			node_pointer z = pos.get_base_ptr();
			this->erase(z);
		}

		/* Swap Function */
		void swap(red_black_tree &other)
		{
			std::swap(this->_end_node, other._end_node);
			std::swap(this->_root, other._root);
			std::swap(this->_size, other._size);
			std::swap(this->_comp, other._comp);
		}

		/* Clear Function */
		void clear()
		{
			if (this->empty())
				return;
			this->_clear(this->_root);
			this->_size = 0;
			this->_end_node->left = nil_node;
		}

		/* Operation Functions */
	public:
		node_pointer successor(value_type value) const { return this->rb_successor(this->search(value)); }

		node_pointer predecessor(value_type value) const { return rb_predecessor(this->search(value)); }

		/* Search Functions */
		node_pointer search(value_type value) const { return this->_search(this->_root, value); }

		template < class Type, class EqualityPredicate, class ComparisonPredicate >
		iterator search(Type value, EqualityPredicate equal, ComparisonPredicate compares) const
		{
			node_pointer x = this->_root;
			while (x != nil_node && !equal(value, x->value))
				x = (compares(value, x->value)) ? x->left : x->right;
			return x != nil_node ? iterator(x) : iterator(this->_end_node);
		}

		/* Allocator Functions */
	public:
		node_allocator_type get_node_allocator() const { return this->node_allocator; }

		/* Private Member Functions */
	private:
		node_pointer _new_node(value_type value) { return new rbt_node(value); }

		static node_pointer _new_node(bool is_black) { return new rbt_node(is_black); }

		/* Modifiers Functions */
	private:
		/* Insert Functions */
		/**
		 * Inserts 'node' following standard binary search tree insertion
		 * @details Restores red-black Properties by calling '_tree_insert_fixup'
		 * @param node Node to insert
		 */
		void _tree_insert(node_pointer node)
		{
			node_pointer y = nil_node;
			node_pointer x = this->_end_node->left;
			while (x != nil_node)
			{
				y = x;
				x = (this->_tree_compare(node->value, x->value)) ? x->left : x->right;
			}
			node->parent = y;
			if (y == nil_node)
			{
				this->_root = node;
				node->parent = this->_end_node;
				this->_end_node->left = this->_root;
				this->_root->is_black = true;
			}
			else
			{
				if (this->_tree_compare(node->value, y->value))
					y->left = node;
				else
					y->right = node;
				this->_tree_insert_fixup(node);
			}
		}

		/**
		 * Performs recoloring and rotations to re-balance the tree
		 */
		void _tree_insert_fixup(node_pointer node)
		{
			node_pointer y;
			while (node != this->_root && !node->parent->is_black)
			{
				if (node->parent == node->parent->parent->left)
				{
					y = node->parent->parent->right;
					if (!y->is_black)
					{
						node = node->parent;
						node->is_black = true;
						node = node->parent;
						node->is_black = (node == this->_root);
						y->is_black = true;
					}
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							_left_rotate(node);
						}
						node->parent->is_black = true;
						node->parent->parent->is_black = false;
						node = node->parent->parent;
						_right_rotate(node);
						break;
					}
				}
				else
				{
					y = node->parent->parent->left;
					if (!y->is_black)
					{
						node = node->parent;
						node->is_black = true;
						node = node->parent;
						node->is_black = (node == this->_root);
						y->is_black = true;
					}
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							this->_right_rotate(node);
						}
						node->parent->is_black = true;
						node->parent->parent->is_black = false;
						node = node->parent->parent;
						this->_left_rotate(node);
						break;
					}
				}
			}
		}

		/* Erase Functions */
		/**
		 * Deletes 'z' following standard binary search tree deletion
		 * @details Restores red-black Properties by calling '_tree_delete_fixup'
		 * @param z
		 */
		void _tree_delete(node_pointer z)
		{
			node_pointer x;
			node_pointer y = z;
			bool was_black = y->is_black;
			if (z->left == nil_node)
			{
				x = z->right;
				this->_transplant(z, z->right);
			}
			else if (z->right == nil_node)
			{
				x = z->left;
				this->_transplant(z, z->left);
			}
			else
			{
				y = rb_min(z->right);
				was_black = y->is_black;
				x = y->right;
				if (y->parent == z)
					/* pivot can be _NIL, storing p info for fixup */
					x->parent = y;
				else
				{
					this->_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				this->_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->is_black = z->is_black;
			}
			--this->_size;
			if (this->_size > 0)
			{
				this->_end_node->left = this->_root;
				this->_root->parent = this->_end_node;
			}
			else
			{
				this->_end_node->left = nil_node;
			}
			if (was_black)
				this->_tree_delete_fixup(x);
		}

		/**
		 * Performs recoloring and rotations to restore red-black properties
		 */
		void _tree_delete_fixup(node_pointer x)
		{
			node_pointer y; /* sibling of x */
			while (x != this->_root && x->is_black)
			{
				if (x == x->parent->left)
				{
					y = x->parent->right;
					if (!y->is_black && y != this->_end_node)
					{
						y->parent->is_black = false;
						y->is_black = true;
						this->_left_rotate(x->parent);
						y = x->parent->right;
					}
					if ((y->left == nil_node || y->left->is_black) && (y->right == nil_node || y->right->is_black))
					{
						y->is_black = false;
						x = x->parent;
					}
					else
					{
						if (y->right->is_black)
						{
							y->left->is_black = true;
							y->is_black = false;
							this->_right_rotate(y);
							y = x->parent->right;
						}
						y->is_black = x->parent->is_black;
						y->parent->is_black = true;
						y->right->is_black = true;
						this->_left_rotate(x->parent);
						x = this->_root;
						this->_end_node->left = x;
						x->parent = this->_end_node;
					}
				}
				else
				{
					y = x->parent->left;
					if (!y->is_black && y != this->_end_node)
					{
						y->parent->is_black = false;
						y->is_black = true;
						this->_right_rotate(x->parent);
						y = x->parent->left;
					}
					if ((y->left == nil_node || y->left->is_black) && (y->right == nil_node || y->right->is_black))
					{
						y->is_black = false;
						x = x->parent;
					}
					else
					{
						if (y->left->is_black)
						{
							y->right->is_black = true;
							y->is_black = false;
							this->_left_rotate(y);
							y = x->parent->left;
						}
						y->is_black = x->parent->is_black;
						y->parent->is_black = true;
						y->left->is_black = true;
						this->_right_rotate(x->parent);
						x = this->_root;
						this->_end_node->left = x;
						x->parent = this->_end_node;
					}
				}
			}
			x->is_black = true;
			this->_end_node->left = this->_root;
			this->_root->parent = this->_end_node;
		}

		/* Clear Functions */
		void _clear(node_pointer x)
		{
			if (x != nil_node && x != this->_end_node)
			{
				this->_clear(x->left);
				this->_clear(x->right);
				rbt_node::destroy(x);
			}
		}

		/* Operation Functions */
	private:
		node_pointer _search(node_pointer x, value_type value) const
		{
			while (x != nil_node && value != x->value)
			{
				if (this->_tree_compare(value, x->value))
					x = x->left;
				else
					x = x->right;
			}
			return x != nil_node ? x : this->_end_node;
		}

		bool _tree_compare(value_type &val_1, value_type &val_2) const
		{
			if (this->_comp(val_1, val_2))
				return true;
			return false;
		}

		/**
		 * Right-rotates at 'x'
		 */
		void _right_rotate(node_pointer x)
		{
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != nil_node)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == this->_end_node)
			{
				this->_root = y;
				this->_end_node->left = y;
			}
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		/**
		 * Left-rotates at 'x'
		 */
		void _left_rotate(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != nil_node)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == this->_end_node)
			{
				this->_root = y;
				this->_end_node->left = y;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		/**
		 * Replaces subtree rooted at 'u' with subtree rooted at 'v'
		 */
		void _transplant(node_pointer u, node_pointer v)
		{
			if (u->parent == this->_end_node)
			{
				this->_root = v;
				this->_end_node->left = v;
			}
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		/* Non Member Functions Overload */

		/**
		 * Finds maximum value in (sub-)tree 'x'
		 * @param x (sub-)tree to find maximum value in
		 * @return Pointer to node with maximum value or 'nil_node' if tree is empty
		 */
		friend node_pointer rb_max(node_pointer x)
		{
			while (x != nil_node && x->right != nil_node)
				x = x->right;
			return (x);
		}

		/**
		 * Finds minimum value in (sub-)tree 'x'
		 * @param x (sub-)tree to find minimum value in
		 * @return Pointer to node with minimum value or 'nil_node' if tree is empty
		 */
		friend node_pointer rb_min(node_pointer x)
		{
			while (x != nil_node && x->left != nil_node)
				x = x->left;
			return (x);
		}

		/**
		 * Finds node with next greater value after 'x'
		 * @return Pointer to node with next greater value, or NULL if not found
		 */
		friend node_pointer rb_successor(node_pointer x)
		{
			if (x == nil_node)
				return (nil_node);
			if (x->right && x->right != nil_node)
				return (rb_min(x->right));
			node_pointer y = x->parent;
			while (y != nil_node && y->parent != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		/**
		 * Finds node with next smallest value before 'x'
		 * @return Pointer to node with next smallest value, or NULL if not found
		 */
		friend node_pointer rb_predecessor(node_pointer x)
		{
			if (x == nil_node)
				return (nil_node);
			if (x->left && x->left != nil_node)
				return (rb_max(x->left));
			node_pointer y = x->parent;
			while (y != nil_node && y->parent != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		/* Recursive Printing Function Implementation */
	private:
		void _pretty_print(const std::string &prefix, node_pointer x, bool is_left, int iter,
						   std::ostream &os = std::cout) const
		{
			++iter;
			if (x && x == nil_node)
			{
				os << "\033[0;34m";
				os << prefix;
				os << (is_left ? "├──" : "└──");
				os << iter;
				os << (is_left ? "L " : "R ");
				os << "\033[0m";
				os << "⁙";
				os << "\033[0;34m"
				   << " " << x << "\033[0m";
				os << std::endl;
			}
			if (x && x != nil_node)
			{
				os << "\033[0;34m";
				os << prefix;
				if (x == _root)
				{
					os << "└──";
					os << iter << "* ";
				}
				else
				{
					os << (is_left ? "├──" : "└──");
					os << iter;
					os << (is_left ? "L " : "R ");
				}
				os << "\033[0m";
				if (x->is_black == false)
					os << "\033[0;31m";
				os << x->value << " "
				   << "\033[0;34m" << x;
				// os << x; // if no << overload
				os << "\033[0m" << std::endl;
				_pretty_print(prefix + (is_left ? "│     " : "      "), x->left, true, iter, os);
				_pretty_print(prefix + (is_left ? "│     " : "      "), x->right, false, iter, os);
			}
		}

	};

	/* Static Member Initialization */

	template < class Value, class Compare, class Allocator >
	typename red_black_tree<Value, Compare, Allocator>::node_allocator_type
			red_black_tree<Value, Compare, Allocator>::node_allocator;

	template < class Value, class Compare, class Allocator >
	typename red_black_tree<Value, Compare, Allocator>::value_allocator_type
			red_black_tree<Value, Compare, Allocator>::value_allocator;

	template < class Value, class Compare, class Allocator >
	typename red_black_tree<Value, Compare, Allocator>::node_pointer
			red_black_tree<Value, Compare, Allocator>::nil_node = _new_node(true);

	template < class Value, class Compare, class Allocator >
	typename red_black_tree<Value, Compare, Allocator>::size_type
			red_black_tree<Value, Compare, Allocator>::_nb_trees = 0;


}