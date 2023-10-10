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


namespace ft {
		template <class Key, 
				class T, 
				class Compare = std::less<Key>,
				class Allocator = std::allocator<pair<const Key, T> > >

		class multimap 
		{
			public:
				// types:
				typedef Key																key_type;
				typedef T 																mapped_type;
				typedef ft::pair<const Key,T> 											value_type;
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
					friend class ft::multimap<Key, T, Compare, Allocator>;

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

				// construct/copy/destroy:
				explicit multimap(const Compare& comp = Compare(), const Allocator& = Allocator());
				
				template <class InputIterator>
				multimap(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& = Allocator());
				
				multimap(const multimap<Key,T,Compare,Allocator>& x);
				
				~multimap();
				
				multimap<Key,T,Compare,Allocator>&
				operator=(const multimap<Key,T,Compare,Allocator>& x);
				
				allocator_type get_allocator() const;

				// iterators:
				iterator begin();
				const_iterator begin() const;
				iterator end();
				const_iterator end() const;
				reverse_iterator rbegin();
				const_reverse_iterator rbegin() const;
				reverse_iterator rend();
				const_reverse_iterator rend() const;

				// capacity:
				bool empty() const;
				size_type size() const;
				size_type max_size() const;

				// modifiers:
				iterator insert(const value_type& x);
				iterator insert(iterator position, const value_type& x);
				template <class InputIterator>
				void insert(InputIterator first, InputIterator last);
				void erase(iterator position);
				size_type erase(const key_type& x);
				void erase(iterator first, iterator last);
				void swap(multimap<Key,T,Compare,Allocator>&);
				void clear();

				// observers:
				key_compare key_comp() const;
				value_compare value_comp() const;

				// map operations:
				iterator find(const key_type& x);
				const_iterator find(const key_type& x) const;
				size_type count(const key_type& x) const;
				iterator lower_bound(const key_type& x);
				const_iterator lower_bound(const key_type& x) const;
				iterator upper_bound(const key_type& x);
				const_iterator upper_bound(const key_type& x) const;
				pair<iterator,iterator>	equal_range(const key_type& x);
				pair<const_iterator,const_iterator>	equal_range(const key_type& x) const;
		};
		
				template <class Key, class T, class Compare, class Allocator>
				bool operator==(const multimap<Key,T,Compare,Allocator>& x,
					const multimap<Key,T,Compare,Allocator>& y);

				template <class Key, class T, class Compare, class Allocator>
				bool operator< (const multimap<Key,T,Compare,Allocator>& x,
					const multimap<Key,T,Compare,Allocator>& y);

				template <class Key, class T, class Compare, class Allocator>
				bool operator!=(const multimap<Key,T,Compare,Allocator>& x,
					const multimap<Key,T,Compare,Allocator>& y);

				template <class Key, class T, class Compare, class Allocator>
				bool operator> (const multimap<Key,T,Compare,Allocator>& x,
					const multimap<Key,T,Compare,Allocator>& y);

				template <class Key, class T, class Compare, class Allocator>
				bool operator>=(const multimap<Key,T,Compare,Allocator>& x,
					const multimap<Key,T,Compare,Allocator>& y);

				template <class Key, class T, class Compare, class Allocator>
				bool operator<=(const multimap<Key,T,Compare,Allocator>& x,
					const multimap<Key,T,Compare,Allocator>& y);

				// specialized algorithms:
				template <class Key, class T, class Compare, class Allocator>
				void swap(multimap<Key,T,Compare,Allocator>& x,
					multimap<Key,T,Compare,Allocator>& y);
}


#endif