
#pragma once

#include "../iterator/rbt_iterator.hpp"
#include "../iterator/iterator_traits.hpp"

namespace ft
{

	template < class T, class Container, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class red_black_tree
	{

		/* Forward Declarations (for member Types) */
	private:
		struct rbt_node;

		/* Member Types */
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef Compare value_compare;
		typedef Allocator value_allocator_type;
		typedef typename value_allocator_type::pointer pointer;
		typedef typename value_allocator_type::const_pointer const_pointer;
		typedef typename value_allocator_type::reference reference;
		typedef typename value_allocator_type::const_reference const_reference;
		typedef typename value_allocator_type::template rebind<rbt_node>::other node_allocator_type;
		typedef typename node_allocator_type::pointer node_pointer;
		typedef typename node_allocator_type::const_pointer const_node_pointer;
		typedef typename node_allocator_type::const_reference const_node_reference;
		typedef typename node_allocator_type::size_type size_type;
		typedef typename node_allocator_type::difference_type difference_type;
		typedef ft::rbt_iterator<value_type, container_type, red_black_tree> iterator;
		typedef ft::rbt_iterator<const value_type, container_type, red_black_tree> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		/* Private Local Classes */
	private:
		struct rbt_node
		{
			rbt_node *parent;
			rbt_node *left;
			rbt_node *right;
			value_type value;
			bool is_black;

			explicit rbt_node(bool is_black = false) : parent(NULL), left(NULL), right(NULL), value(),
													   is_black(is_black) { }

			explicit rbt_node(value_type val) : parent(nil_node), left(nil_node), right(nil_node), value(val),
												is_black(false) { }

			rbt_node(const rbt_node &other)
					: parent(nil_node), left(nil_node), right(nil_node), value(other.value), is_black(false) { }

			void destroy()
			{
				red_black_tree::node_allocator.destroy(this);
				red_black_tree::node_allocator.deallocate(this, 1);
			}

			static void destroy_node(node_pointer &node)
			{
				red_black_tree::node_allocator.destroy(node);
				red_black_tree::node_allocator.deallocate(node, 1);
				node = NULL;
			}
		};


		/* Protected Members */
	protected:
		/* Static Members */
		static node_allocator_type node_allocator;
		static value_allocator_type value_allocator;
		static node_pointer nil_node;

		/* Private members */
	private:
		node_pointer _end_node;
		node_pointer _root;
		size_type _size;
		value_compare _comp;
		/* Static Members */
		static size_type _nb_trees;


		/* Constructors */
	public:

		red_black_tree() : _end_node(_new_node(false)), _size(0)
		{
			_end_node->left = nil_node;
			++_nb_trees;
		}

		explicit red_black_tree(const Compare &c, const Allocator &alloc = Allocator()) : _root(nil_node), _size(0),
																						  _comp(c)
		{
			value_allocator = alloc;
			_end_node->left = nil_node;
			++_nb_trees;
		}

		red_black_tree(const red_black_tree &other) : _end_node(_new_node(false)), _size(0), _comp(other._comp)
		{
			_end_node->left = nil_node;
			++_nb_trees;
			for (const_iterator it = other.begin(); it != other.end(); it++)
				insert(*it);
		}

		/* Destructor */
	public:
		virtual ~red_black_tree()
		{
			if (!empty())
				_clear(_root);
			_end_node->destroy();
			--_nb_trees;
		}

		/* Public Member Functions */
	public:
		void print_tree() const
		{
			_pretty_print("", _end_node->left, false, -1);
			std::cout << std::endl;
		}

		/* Iterator Functions */
	public:
		iterator begin() { return empty() ? end() : iterator(min()); }

		const_iterator begin() const { return empty() ? end() : const_iterator(min()); }

		iterator end() { return iterator(_end_node); }

		const_iterator end() const { return const_iterator(_end_node); }

		reverse_iterator rbegin() { return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }

		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* Modifiers Functions */
	public:
		void swap(red_black_tree &other)
		{
			std::swap(_end_node, other._end_node);
			std::swap(_root, other._root);
			std::swap(_size, other._size);
			std::swap(_comp, other._comp);
		}

		void clear()
		{
			if (empty())
				return;
			_clear(_root);
			_size = 0;
			_end_node->left = nil_node;
		}

		/* Insertion */
		/**
		 * Allocates a node containing 'value' and inserts it into the tree
		 * @param value
		 * @return new node
		 */
		iterator insert(value_type value)
		{
			node_pointer x = _new_node(value);
			_tree_insert(x);
			++_size;
			_end_node->left = _root;
			_root->parent = _end_node;
			return iterator(x);
		}

		/* Deletion */
		/**
		 * Searches and erases 'z' (if found)
		 * @param z node to erase
		 */
		void erase(node_pointer z)
		{
			if (!z || z == nil_node || z == _end_node)
				return;
			node_pointer tmp = z;
			_tree_delete(z);
			rbt_node::destroy_node(tmp);
		}

		/**
		 * Searches and erases from 'first' to 'last' (if found)
		 * @param first First element in Range
		 * @param last Last element in Range
		 */
		void erase(iterator first, iterator last)
		{
			iterator it = first;
			while (it != last)
			{
				node_pointer z = it.get_base_ptr();
				node_pointer tmp = z;
				++it;
				if (!z || z == nil_node || z == _end_node)
					break;
				_tree_delete(z);
				rbt_node::destroy_node(tmp);
			}
		}

		/**
		 * Searches and erases 'value' (if found)
		 * @param value Value to erase
		 */
		void erase(const_reference value)
		{
			node_pointer z = search(value);
			erase(z);
		}

		/**
		 * Searches and erases at position 'pos'
		 * @param pos Position to erase
		 */
		void erase(iterator pos)
		{
			node_pointer z = pos.get_base_ptr();
			erase(z);
		}


		/* Relational Operators Overload */
	public:
		red_black_tree &operator=(const red_black_tree &other)
		{
			clear();
			for (const_iterator it = other.begin(); it != other.end(); it++)
			{
				insert(*it);
			}
			return *this;
		}

		/* Capacity Functions */
	public:
		bool empty() const { return _size == 0; }

		size_type size() const { return _size; }

		node_pointer min() const { return empty() ? _end_node : rb_min(_root); }

		node_pointer max() const { return empty() ? _end_node : rb_max(_root); }

		/* Operation Functions */
	public:
		node_pointer successor(value_type value) const { return rb_successor(search(value)); }

		node_pointer predecessor(value_type value) const { return rb_predecessor(search(value)); }

		node_pointer search(value_type value) const { return _search(_root, value); }

		template < class Type, class EqualityPredicate, class ComparisonPredicate >
		iterator search(Type value, EqualityPredicate equal, ComparisonPredicate compares) const
		{
			node_pointer x = _root;
			while (x != nil_node && !equal(value, x->value))
				x = (compares(value, x->value)) ? x->left : x->right;
			return x != nil_node ? iterator(x) : iterator(_end_node);
		}

		/**
		 * @return pointer to node with maximum value
		 */
		friend node_pointer rb_max(node_pointer x)
		{
			while (x != nil_node && x->right != nil_node)
				x = x->right;
			return x;
		}

		/**
		 * @return pointer to node with minimum value
		 */
		friend node_pointer rb_min(node_pointer x)
		{
			while (x != nil_node && x->left != nil_node)
				x = x->left;
			return x;
		}

		/**
		 * @return pointer to node with next greater value
		 */
		friend node_pointer rb_successor(node_pointer x)
		{
			if (x == nil_node)
				return nil_node;
			if (x->right && x->right != nil_node)
				return rb_min(x->right);
			node_pointer y = x->parent;
			while (y != nil_node && y->parent != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		/**
		 * @return pointer to node with next smallest value
		 */
		friend node_pointer rb_predecessor(node_pointer x)
		{
			if (x == nil_node)
				return nil_node;
			if (x->left && x->left != nil_node)
				return rb_max(x->left);
			node_pointer y = x->parent;
			while (y != nil_node && y->parent != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		/* Allocator Functions */
	public:
		node_allocator_type get_node_allocator() const { return node_allocator; }

		/* Private Member Functions */
	private:
		node_pointer _new_node(value_type value)
		{
			node_pointer x = node_allocator.allocate(1);
			node_allocator.construct(x, const_node_reference(value));
			return x;
		}

		static node_pointer _new_node(bool is_black)
		{
			node_pointer x = node_allocator.allocate(1);
			node_allocator.construct(x, const_node_reference(is_black));
			return x;
		}

		/**
		 * Recursively destroys all nodes in (sub-)tree 'x'
		 */
		void _clear(node_pointer tree)
		{
			if (tree != nil_node && tree != _end_node)
			{
				_clear(tree->left);
				_clear(tree->right);
				rbt_node::destroy_node(tree);
			}
		}

		bool _tree_compare(value_type &val_1, value_type &val_2) const
		{
			if (_comp(val_1, val_2))
				return true;
			return false;
		}

		/**
		 * Searches for a node containing 'value' in a (sub-)tree rooted at 'tree'
		 * @param tree (sub-)tree to search for value
		 * @param value value to search for
		 * @return pointer to the found node, or _nil_node if not found
		 */
		node_pointer _search(node_pointer tree, value_type value) const
		{
			while (tree != nil_node && value != tree->value)
			{
				if (_tree_compare(value, tree->value))
					tree = tree->left;
				else
					tree = tree->right;
			}
			return tree != nil_node ? tree : _end_node;
		}

		/* Rotate */
		void _right_rotate(node_pointer x)
		{
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != nil_node)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _end_node)
			{
				_root = y;
				_end_node->left = y;
			}
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void _left_rotate(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != nil_node)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _end_node)
			{
				_root = y;
				_end_node->left = y;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		/* Transplant */
		/**
		 * Replaces subtree rooted at 'u' with subtree rooted at 'v'
		 */
		void _transplant(node_pointer u, node_pointer v)
		{
			if (u->parent == _end_node)
			{
				_root = v;
				_end_node->left = v;
			}
				// else if (u->parent == _nil_node)
				// 	_end_node = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void _tree_insert(node_pointer node)
		{
			node_pointer y = nil_node;
			node_pointer x = _end_node->left;
			while (x != nil_node)
			{
				y = x;
				x = (_tree_compare(node->value, x->value)) ? x->left : x->right;
			}
			node->parent = y;
			if (y == nil_node)
			{
				_root = node;
				node->parent = _end_node;
				_end_node->left = _root;
				_root->is_black = true;
			}
			else
			{
				if (_tree_compare(node->value, y->value))
					y->left = node;
				else
					y->right = node;
				_tree_insert_fixup(node);
			}
		}

		void _tree_insert_fixup(node_pointer node)
		{
			node_pointer y;
			while (node != _root && !node->parent->is_black)
			{
				if (node->parent == node->parent->parent->left)
				{
					y = node->parent->parent->right;
					if (!y->is_black)
					{
						node = node->parent;
						node->is_black = true;
						node = node->parent;
						node->is_black = (node == _root);
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
					if (y && !y->is_black)
					{
						node = node->parent;
						node->is_black = true;
						node = node->parent;
						node->is_black = (node == _root);
						y->is_black = true;
					}
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							_right_rotate(node);
						}
						node->parent->is_black = true;
						node->parent->parent->is_black = false;
						node = node->parent->parent;
						_left_rotate(node);
						break;
					}
				}
			}
		}

		void _tree_delete(node_pointer z)
		{
			// node_pointer tmp_z = z;
			node_pointer x;
			node_pointer y = z;
			bool was_black = y->is_black;
			if (z->left == nil_node)
			{
				x = z->right;
				_transplant(z, z->right);
			}
			else if (z->right == nil_node)
			{
				x = z->left;
				_transplant(z, z->left);
			}
			else
			{
				y = rb_min(z->right);
				was_black = y->is_black;
				x = y->right;
				if (y->parent == z)
					/* pivot can be _nil_node, storing p info for fixup */
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->is_black = z->is_black;
			}
			--_size;
			if (_size > 0)
			{
				_end_node->left = _root;
				_root->parent = _end_node;
			}
			else
			{
				_end_node->left = nil_node;
			}
			if (was_black)
				_tree_delete_fixup(x);
		}

		void _tree_delete_fixup(node_pointer x)
		{
			node_pointer y; /* sibling of x */
			while (x != _root && x->is_black)
			{
				if (x == x->parent->left)
				{
					y = x->parent->right;
					if (!y->is_black && y != _end_node)
					{
						y->parent->is_black = false;
						y->is_black = true;
						_left_rotate(x->parent);
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
							_right_rotate(y);
							y = x->parent->right;
						}
						y->is_black = x->parent->is_black;
						y->parent->is_black = true;
						y->right->is_black = true;
						_left_rotate(x->parent);
						x = _root;
						_end_node->left = x;
						x->parent = _end_node;
					}
				}
				else
				{
					y = x->parent->left;
					if (!y->is_black && y != _end_node)
					{
						y->parent->is_black = false;
						y->is_black = true;
						_right_rotate(x->parent);
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
							_left_rotate(y);
							y = x->parent->left;
						}
						y->is_black = x->parent->is_black;
						y->parent->is_black = true;
						y->left->is_black = true;
						_right_rotate(x->parent);
						x = _root;
						_end_node->left = x;
						x->parent = _end_node;
					}
				}
			}
			x->is_black = true;
			_end_node->left = _root;
			_root->parent = _end_node;
		}

		/* Recursive core of print_tree() */
		void _pretty_print(const std::string &prefix, node_pointer x, bool is_left, int iter) const
		{
			++iter;
			if (x && x == nil_node)
			{
				std::cout << "\033[0;34m";
				std::cout << prefix;
				std::cout << (is_left ? "├──" : "└──");
				std::cout << iter;
				std::cout << (is_left ? "L " : "R ");
				std::cout << "\033[0m";
				std::cout << "⁙";
				std::cout << "\033[0;34m" << " " << x << "\033[0m";
				std::cout << std::endl;
			}
			if (x && x != nil_node)
			{
				std::cout << "\033[0;34m";
				std::cout << prefix;
				if (x == _root)
				{
					std::cout << "└──";
					std::cout << iter << "* ";
				}
				else
				{
					std::cout << (is_left ? "├──" : "└──");
					std::cout << iter;
					std::cout << (is_left ? "L " : "R ");
				}
				std::cout << "\033[0m";
				if (x->is_black == false)
					std::cout << "\033[0;31m";
				std::cout << x->value << " " << "\033[0;34m" << x;
				// std::cout << x; // if no << overload
				std::cout << "\033[0m" << std::endl;
				_pretty_print(prefix + (is_left ? "│     " : "      "), x->left, true, iter);
				_pretty_print(prefix + (is_left ? "│     " : "      "), x->right, false, iter);
			}
		}

	};

	/* Static Member Initialization */
	template < class T, class Compare, class Allocator >
	typename red_black_tree<T, Compare, Allocator>::node_allocator_type red_black_tree<T, Compare, Allocator>::node_allocator = typename red_black_tree<T, Compare, Allocator>::node_allocator_type();

	template < class T, class Compare, class Allocator >
	typename red_black_tree<T, Compare, Allocator>::value_allocator_type red_black_tree<T, Compare, Allocator>::value_allocator = typename red_black_tree<T, Compare, Allocator>::value_allocator_type();

	template < class T, class Compare, class Allocator >
	typename red_black_tree<T, Compare, Allocator>::node_pointer red_black_tree<T, Compare, Allocator>::nil_node = typename red_black_tree<T, Compare, Allocator>::node_pointer();

	template < class T, class Compare, class Allocator >
	typename red_black_tree<T, Compare, Allocator>::size_type red_black_tree<T, Compare, Allocator>::_nb_trees = typename red_black_tree<T, Compare, Allocator>::size_type();
}