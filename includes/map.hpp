#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "iterator_traits.hpp"
#include "rbt.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "bi_directional_it.hpp"
#include "rev_it.hpp"

#define BLACK 	0
#define RED 	1

// https://cplusplus.com/reference/map/map/

namespace ft
{
	template<class T>
	class node;

    template < class Key,                                     // map::key_type, Type of the keys. Each element in a map is uniquely identified by its key value.
        	class T,                                       // map::mapped_type, Type of the mapped value. Each element in a map stores some data as its mapped value.
        	class Compare = std::less<Key>,                     // map::key_compare, A binary predicate that takes two element keys as arguments and returns a bool
        	class Allocator = std::allocator<ft::pair<const Key,T> > >   // map::allocator_type, Type of the allocator object used to define the storage allocation model.

    class map
	{
        public:

			typedef Key 															key_type;
			typedef T 																mapped_type;
			typedef ft::pair<const Key, T> 											value_type;
			typedef ft::pair<const Key, const T> 									const_value_type;
			typedef Compare 														key_compare;
			typedef Allocator 														allocator_type;

			typedef node<value_type>												node_type;
			typedef node<value_type>												*node_ptr;
			typedef typename Allocator::template rebind<node<mapped_type> >::other	node_alloc;

			typedef typename Allocator::reference 									reference;
			typedef typename Allocator::const_reference 							const_reference;
			typedef typename ft::rbt<value_type, key_compare>::iterator				iterator;
			typedef typename ft::rbt<value_type, key_compare>::const_iterator		const_iterator;
			typedef size_t 															size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef typename Allocator::pointer 									pointer;
			typedef typename Allocator::const_pointer 								const_pointer;
			typedef ft::reverse_iterator<iterator> 									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 							const_reverse_iterator;


			class value_compare
				: public std::binary_function<value_type,value_type,bool> 
			{
				friend class ft::map<Key, T, Compare, Allocator>;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			
			private:
				size_type							_size;
				allocator_type						_alloc;
				node_alloc							_node_alloc;
				key_compare							_key_comp;
				rbt<value_type, key_compare>		_rbt;

			public:

			// 23.3.1.1 construct/copy/destroy:

			// Effects: Constructs an empty map using the specified comparison object and allocator.
			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : 
					_size(0), _alloc(alloc), _key_comp(comp) {}

			// Effects: Constructs an empty map using the specified comparison object and allocator, and inserts elements from the range [first,last)
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(),
				const Allocator& alloc = Allocator()) : _size(0), _alloc(alloc), _key_comp(comp)
			{
				for(; first != last; first++)
					ft::pair<iterator, bool> res = insert(*first);
			}

			// copy constructor
			map(const map<Key,T,Compare,Allocator>& x)
			{
				*this = x;
			}

			~map()
			{
				clear();
			}

			map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x)
			{
				_alloc = x._alloc;
				_node_alloc = x._node_alloc;
				_key_comp = x._key_comp;
				_rbt.clear();
				insert(x.begin(), x.end());
				_size = x._size;
				return (*this);
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
				return (_rbt.end());
			}

			const_iterator end() const
			{
				return (_rbt.const_end()) ;
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
				return const_reverse_iterator(_rbt.const_begin());
			}

			// // capacity:
			bool empty() const
			{
				return (_rbt.getSize() == 0);
			}

			size_type size() const
			{
				return _rbt.getSize();
			}

			size_type max_size() const
			{
				return (_rbt.getMaxsize());
			}

			// // 23.3.1.2 element access:
			
			// Returns: (*((insert(make_pair(x, T()))).first)).second :
			// If k matches the key of an element in the container, the function returns a reference to its mapped value.
			// If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value. 
			
			mapped_type& operator[](const key_type& x)
			{
				ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());

				ft::pair<iterator, bool> r = insert(p);
				iterator it = r.first;
				mapped_type &m = it->second; 

				return m;
			}

			// // modifiers:

			ft::pair<iterator, bool> insert(const value_type& x)
			{
				ft::pair<iterator, bool> res = _rbt.add_node(x);
				return res;
			}

			// If a value_type with the same key as x is not present in the map, then x is inserted into the map. Otherwise, the pair is not inserted. A position may be supplied as a hint regarding where to do the insertion. If the insertion may be done right after position then it takes amortized constant time. Otherwise it will take O(log N) time.
			iterator insert(iterator position, const value_type& x)
			{
				(void) position;
				return (insert(x).first);
			}

			// Copies of each element in the range [first, last) which posess a unique key, one not already in the map, will be inserted into the map. The iterators first and last must return values of type pair<T1,T2>. This operation takes approximately O(N*log(size()+N)) time.
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
				{
					insert(*first);
				}
			}

			// Deletes the map element pointed to by the iterator position. Returns an iterator pointing to the element following the deleted element, or end() if the deleted item was the last one in this list.
			void	erase(iterator position)
			{
				if (_rbt.erase(position->first) == 0)
					return;
			}

			// Deletes the element with the key value x from the map, if one exists. Returns 1 if x existed in the map, 0 otherwise.
			size_type erase(const key_type& x)
			{
				size_type res = _rbt.erase(x);

				if (res == 0)
					return (0);
				return (1);
			}

			// Providing the iterators first and last point to the same map and last is reachable from first, all elements in the range (first, last) will be deleted from the map. Returns an iterator pointing to the element following the last deleted element, or end() if there were no elements after the deleted range.
			void	erase (iterator first, iterator last)
			{
				iterator	res;
				
				for (; first != last; )
				{
					res = first;
					first++;
					_rbt.erase(res->first);
				}
			}

			// Swaps the contents of the map x with the current map, *this.

			void swap(map<Key,T,Compare,Allocator>&x)
			{
				size_type	tmp_size = x._size;
				allocator_type	tmp_alloc = x._alloc;
				node_alloc	tmp_node_alloc = x._node_alloc;
				key_compare	tmp_key_comp = x._key_comp;

				x._size =_size;
				x._alloc = _alloc;
				x._node_alloc = _node_alloc;
				x._key_comp = _key_comp;

				_size = tmp_size;
				_alloc = tmp_alloc;
				_node_alloc = tmp_node_alloc;
				_key_comp = tmp_key_comp;
				_rbt.swap(x._rbt);
			}

			void clear()
			{
				_rbt.clear();
			}

			// // observers:

			// Returns a function object capable of comparing key values using the comparison operation, Compare, of the current map.
			key_compare key_comp() const
			{
				return (_key_comp);
			}

			// Returns a function object capable of comparing pair<const Key, T> values using the comparison operation, Compare, of the current map. This function is identical to key_comp for sets.
			value_compare value_comp() const
			{
				return value_compare(_key_comp);
			}

			// // 23.3.1.3 map operations:

			// Searches the map for a pair with the key value x and returns an iterator to that pair if it is found. 
			// If such a pair is not found the value end() is returned.

			iterator find(const key_type& x)
			{
				return (_rbt.find(x));
			}

			const_iterator find(const key_type& x) const
			{
				return (const_iterator(_rbt.find(x)));
			}

			// // Returns a 1 if a value with the key x exists in the map, otherwise returns a 0.
			size_type count(const key_type& x) const
			{
				if (_rbt.find(x) != _rbt.end())
					return (1);
				return (0);
			}

			// https://cplusplus.com/reference/algorithm/lower_bound/
			// Returns a reference to the first entry with a key greater than or equal to x.
			
			iterator lower_bound(const key_type& x) const
			{
				return (_rbt.lower_bound(x));
			}
			

			const_iterator const_lower_bound(const key_type& x) const
			{
				return (_rbt.const_lower_bound(x));
			}

			// Returns a reference to the first entry with a key less than or equal to x.
			iterator upper_bound(const key_type& x) const
			{
				return (_rbt.upper_bound(x));
			}

			const_iterator const_upper_bound(const key_type& x) const
			{
				return (_rbt.upper_bound(x));
			}

			// Returns the pair, (lower_bound(x), upper_bound(x)).
			pair<iterator,iterator>	equal_range(const key_type& x)
			{
				return (ft::make_pair(lower_bound(x), upper_bound(x)));
			}

			// Returns the pair, (lower_bound(x), upper_bound(x)).
			pair<const_iterator,const_iterator>	equal_range(const key_type& x) const
			{
				return (ft::make_pair(lower_bound(x), upper_bound(x)));
			}

			private:
				size_t	get_rbtsize() const
				{
					return (_rbt.getSize());
				}


	};

	// Returns true if all elements in x are element-wise equal to all elements in y,
	//  using (T::operator==). Otherwise it returns false.
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		if (x.get_rbtsize() != y.get_rbtsize())
			return false;
		return (ft::equal(x.begin(), x.end(), y.begin()));
	}

	// Returns true if x is lexicographically less than y. Otherwise, it returns false.
	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return (y < x); // equivalent de !(x < y)
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(x < y); // equivalent de x <= y
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif