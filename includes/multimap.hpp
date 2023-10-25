#ifndef MULTIMAP_HPP
#define MULTIMAP_HPP

#include <iostream>
#include "iterator_traits.hpp"
#include "rbt.hpp"
#include "pair.hpp"
#include "make_pair.hpp"
#include "bi_directional_it.hpp"
#include "rev_it.hpp"


// multimap support equivalent keys (!= map which supports unique keys)
// A multimap is a kind of associative container that supports equivalent keys (possibly containing multiple
// copies of the same key value) and provides for fast retrieval of values of another type T based on the keys.
// Multimap supports bidirectional iterators

// a_uniq et a_eq p465 de l iso 
// a_uniq.insert(t) > returns pair<iterator,bool>
//                  =   inserts t if and only if there is no element
//                     in the container with key equivalent to
//                     the key of t. The bool component of
//                     the returned pair indicates whether the
//                     insertion takes place and the iterator
//                     component of the pair points to the ele-
//                     ment with key equivalent to the key of t

// a_eq.insert(t) > returns iterator 
//                  =   inserts t and returns the iterator pointing
//                     to the newly inserted element.


namespace ft 
{
	template<class T>
	class node;

	template <class K, 
			class T, 
			class Compare = std::less<K>,
			class Allocator = std::allocator<pair<const K, T> > >

	class multimap 
	{
		public:
			// types:
			typedef K																key_type;
			typedef T 																mapped_type;
			typedef ft::pair<const K,T> 											value_type;
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
				friend class ft::multimap<K, T, Compare, Allocator>;
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

			// construct/copy/destroy:
			explicit multimap(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _size(0), _alloc(alloc), _key_comp(comp) 
			{}
				
			template <class InputIterator>
			multimap(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _size(0), _alloc(alloc), _key_comp(comp)
			{
				for(; first != last; first++)
				ft::pair<iterator, bool> res = insert(*first);
			}
				
			multimap(const multimap<K,T,Compare,Allocator>& x)
			{
				*this = x;
			}
				
			~multimap()
			{
				clear();
			}
				
			multimap<K,T,Compare,Allocator>& operator=(const multimap<K,T,Compare,Allocator>& x)
			{
				_alloc = x._alloc;
				_node_alloc = x._node_alloc;
				_key_comp = x._key_comp;
				_rbt.clear();
				insert(x.begin(), x.end());
				_size = x._size;
				return (*this);
			}

rbt<value_type, key_compare> get_rbt() const
{
	return (_rbt);
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

			// capacity:
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
// PB map et mmap en comparaison a la compil (meme results MAIS difference dans le 1er insert avec le return ft::pair?)
			// modifiers:
			// ft::pair<iterator, bool> insert(const value_type& x)
			iterator insert(const value_type& x)
			{

				iterator it = _rbt.add_node_mmap(x);
				std::cout << "node " << (*it).first << " value " << (*it).second << "adresse" << &it << std::endl;
				return (_rbt.add_node_mmap(x));
			}

			iterator insert(iterator position, const value_type& x)
			{
				(void) position;
				return (insert(x));
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			}

			void erase(iterator position)
			{
				if (_rbt.erase(position->first) == 0)
					return;
			}

			size_type erase(const key_type& x)
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
					_rbt.erase(res->first);
				}
			}

			void swap(multimap<K,T,Compare,Allocator>& x)
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

			// observers:
			key_compare key_comp() const
			{
				return (_key_comp);
			}

			value_compare value_comp() const
			{
				return value_compare(_key_comp);
			}

			// map operations:
			iterator find(const key_type& x)
			{
				return (_rbt.find(x));
			}

			const_iterator find(const key_type& x) const
			{
				return (const_iterator(_rbt.find(x)));
			}

			size_type count(const key_type& x) const
			{
				if (_rbt.find(x) != _rbt.end())
					return (1);
				return (0);
			}

			iterator lower_bound(const key_type& x)
			{
				return (_rbt.lower_bound(x));
			}
			
			const_iterator lower_bound(const key_type& x) const
			{
				return (_rbt.const_lower_bound(x));
			}

			iterator upper_bound(const key_type& x)
			{
				return (_rbt.upper_bound(x));
			}

			const_iterator upper_bound(const key_type& x) const
			{
				return (_rbt.upper_bound(x));
			}

			pair<iterator,iterator>	equal_range(const key_type& x)
			{
				return (ft::make_pair(lower_bound(x), upper_bound(x)));
			}

			pair<const_iterator,const_iterator>	equal_range(const key_type& x) const
			{
				return (ft::make_pair(lower_bound(x), upper_bound(x)));
			}
			
		};
		
			template <class K, class T, class Compare, class Allocator>
			bool operator==(const multimap<K,T,Compare,Allocator>& x,
				const multimap<K,T,Compare,Allocator>& y);

			template <class K, class T, class Compare, class Allocator>
			bool operator< (const multimap<K,T,Compare,Allocator>& x,
				const multimap<K,T,Compare,Allocator>& y);

			template <class K, class T, class Compare, class Allocator>
			bool operator!=(const multimap<K,T,Compare,Allocator>& x,
				const multimap<K,T,Compare,Allocator>& y);

			template <class K, class T, class Compare, class Allocator>
			bool operator> (const multimap<K,T,Compare,Allocator>& x,
				const multimap<K,T,Compare,Allocator>& y);

			template <class K, class T, class Compare, class Allocator>
			bool operator>=(const multimap<K,T,Compare,Allocator>& x,
				const multimap<K,T,Compare,Allocator>& y);

			template <class K, class T, class Compare, class Allocator>
			bool operator<=(const multimap<K,T,Compare,Allocator>& x,
				const multimap<K,T,Compare,Allocator>& y);

			// specialized algorithms:
			template <class K, class T, class Compare, class Allocator>
			void swap(multimap<K,T,Compare,Allocator>& x,
				multimap<K,T,Compare,Allocator>& y);
}


#endif