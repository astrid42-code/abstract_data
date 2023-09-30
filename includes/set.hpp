#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "iterator_traits.hpp"
#include "rbt_set.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "bi_directional_it.hpp"
#include "rev_it.hpp"

#define BLACK 	0
#define RED 	1

// https://cplusplus.com/reference/set/set/?kw=set

namespace ft
{
	template	<class Key,
				class Compare = std::less<Key>,
				class Allocator = std::allocator<Key> >
	class set
	{
		public:

			typedef Key																key_type;
			typedef Key																value_type;
			typedef Compare															key_compare;
			typedef Compare															value_compare;
			typedef Allocator														allocator_type;
			typedef typename Allocator::reference									reference;
			typedef typename Allocator::const_reference 							const_reference;
			typedef typename Allocator::pointer										pointer;
			typedef typename Allocator::const_pointer								const_pointer;

			typedef node<key_type>												node_type;
			typedef node<key_type>												*node_ptr;
			typedef typename Allocator::template rebind<node<key_type> >::other	node_alloc;

			typedef typename ft::rbt_set<key_type, key_compare>::iterator				iterator;
			typedef typename ft::rbt_set<key_type, key_compare>::const_iterator			const_iterator;

			typedef size_t 															size_type; // See 23.1
			typedef std::ptrdiff_t													difference_type;// See 23.1

			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		private:
			size_type							_size;
			allocator_type						_alloc;
			key_compare							_key_comp;
			rbt_set<key_type, key_compare>		_rbt;
		
		public:
		// construct/copy/destroy:
			explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator()): 
					_size(0), _alloc(alloc), _key_comp(comp) { }

			template <class InputIterator>
			set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : 
					_size(0), _alloc(alloc), _key_comp(comp) 
			{
				// std::cout << "Welcome in set range" << std::endl;
				for(; first != last; first++)
				{
					ft::pair<iterator, bool> res = insert(*first);
				}
			}

			set(const set<Key,Compare,Allocator>& x)
			{
				*this = x;
			}

			~set()
			{
				clear();
			}

			set<Key,Compare,Allocator>& 
			operator=(const set<Key,Compare,Allocator>& x)
			{
				_alloc = x._alloc;
				_key_comp = x._key_comp;
				_rbt.clear();
				insert(x.begin(), x.end());
				_size = x._size;
				return (*this);
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			// iterators:
			iterator begin()
			{
				return _rbt.begin();
			}

			const_iterator begin() const
			{
				return _rbt.const_begin();
			}

			iterator end()
			{
				return _rbt.end();
			}

			const_iterator end() const
			{
				return _rbt.const_end();
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(_rbt.end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(_rbt.end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(_rbt.begin());
			}

			const_reverse_iterator rend() const
			{
				return reverse_iterator(_rbt.const_begin());
			}

			// capacity:
			bool empty() const
			{
				return (_rbt.getSize() == 0);
			}

			size_type size() const
			{
				return (_rbt.getSize());
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			// modifiers:
			pair<iterator,bool> insert(const value_type& x)
			{
				ft::pair<iterator, bool> res = _rbt.add_node(x);
				return res;
			}

			iterator insert(iterator position, const value_type& x)
			{
				(void) position;
				return (insert(x).first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
				{
					insert(*first);
				}
			}

			void erase(iterator position)
			{
				if (_rbt.erase(position.get_node()->pair) == 0)
					return;
			}

			size_type erase(const value_type& x)
			{
				size_type res = _rbt.erase(x);

				if (res == 0)
					return (0);
				return (1);
			}

			void erase(iterator first, iterator last)
			{
				iterator	res;
				
				for (; first != last; )
				{
					res = first;
					first++;
					_rbt.erase(res.get_node()->pair);
				}
			}

			void swap(set<Key,Compare,Allocator>& x)
			{
				size_type	tmp_size = x._size;
				allocator_type	tmp_alloc = x._alloc;
				key_compare	tmp_key_comp = x._key_comp;

				x._size =_size;
				x._alloc = _alloc;
				x._key_comp = _key_comp;

				_size = tmp_size;
				_alloc = tmp_alloc;
				_key_comp = tmp_key_comp;
				_rbt.swap(x._rbt);
			}

			void clear()
			{
				_rbt.clear();
			}

			// observers:
			key_compare key_comp() const
			{
				return (_key_comp);
			}

			value_compare value_comp() const
			{
				return value_compare(_key_comp);
			}

			// set operations:
			iterator find(const key_type& x) const
			{
				return (_rbt.find(x));
			}

			size_type count(const key_type& x) const
			{
				if (_rbt.find(x) != _rbt.end())
					return (1);
				return (0);
			}

			iterator lower_bound(const value_type& x) const
			{
				return (_rbt.lower_bound(x));
			}

			iterator upper_bound(const value_type& x) const
			{
				return (_rbt.upper_bound(x));
			}

			pair<iterator,iterator> equal_range(const value_type& x) const
			{
				return (ft::make_pair(lower_bound(x), upper_bound(x)));
			}
	};

	template <class Key, class Compare, class Allocator>
	bool operator==(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y)
	{
		if (x.size() != y.size())
			return false;
		return (ft::equal(x.begin(), x.end(), y.begin()));
	}

	template <class Key, class Compare, class Allocator>
	bool operator< (const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y)
	{
		return !(x == y);
	}

	template <class Key, class Compare, class Allocator>
	bool operator> (const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y)
	{
		return (y < x); // equivalent de !(x < y)
	}

	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y)
	{
		return !(x < y); // equivalent de x <= y
	}

	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key,Compare,Allocator>& x,
	const set<Key,Compare,Allocator>& y)
	{
		return !(y < x);
	}

	// specialized algorithms:
	template <class Key, class Compare, class Allocator>
	void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y)
	{
		x.swap(y);
	}

}

#endif