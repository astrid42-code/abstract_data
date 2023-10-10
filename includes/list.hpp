#ifndef list_HPP
#define list_HPP

#include <iostream>
#include <string>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rev_it.hpp"
#include "bi_directional_it.hpp"

// A sequence is a kind of container that organizes a finite set of objects,
// all of the same type, into a strictly linear arrangement. 
// list should be used when there are frequent insertions and deletions 
// from the middle of the sequence.


namespace ft 
{
	template <class T, class Alloc = std::allocator<T> >
	class list
	{
		public:
			// types:
			typedef typename Alloc::reference 				reference;
			typedef typename Alloc::const_reference 		const_reference;
			typedef T* 										iterator;
			typedef const T* 								const_iterator;
			typedef size_t 									size_type;
			typedef std::ptrdiff_t 							difference_type;
			typedef T 										value_type;
			typedef Alloc									alloc_type;
			typedef typename Alloc::pointer 				pointer;
			typedef typename Alloc::const_pointer 			const_pointer;
			typedef std::reverse_iterator<iterator> 		reverse_iterator;
			typedef std::reverse_iterator<const_iterator> 	const_reverse_iterator;
			

			private:
			size_type 	_size; // nb of objects in my list
			size_type 	_capacity; // total capacity of my list (distance between first and last)
			Alloc		_alloc; // alloc object
			pointer		_begin; // ptr to begining of memory block
			
		
			public:

			// 23.2.2.1 construct/copy/destroy:
			explicit list(const Alloc &alloc = Alloc()) : _size(0), _capacity(0), _alloc(alloc), _begin(NULL) { }
			
			explicit list(size_type	n, const T&	value = T(), const Alloc& = Alloc());
			
			template <class InputIterator>
			list(InputIterator first, InputIterator	last, const Alloc& = Alloc());

			list(const list<T,Alloc>& x);

			~list();

			list<T,Alloc>& operator=(const list<T,Alloc>& x);

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);

			void assign(size_type n, const T& t);
			alloc_type get_allocator() const;

			// iterators:
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			// 23.2.2.2 capacity:
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			void resize(size_type sz, T c = T());

			// element access:
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// 23.2.2.3 modifiers:
			void push_front(const T& x);
			void pop_front();
			void push_back(const T&	x);
			void pop_back();
			iterator insert(iterator position, const T&	x);
			void insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void insert(iterator position, InputIterator first,	InputIterator last);
			iterator erase(iterator	position);
			iterator erase(iterator	position, iterator last);
			void swap(list<T,Allocator>&);
			void clear();

			// 23.2.2.4 list operations:
			void splice(iterator position, list<T,Alloc>& x);
			void splice(iterator position, list<T,Alloc>& x, iterator i);
			void splice(iterator position, list<T,Alloc>& x, iterator first, iterator last);
			void remove(const T& value);

			template <class Predicate> void remove_if(Predicate	pred);
			void unique();

			template <class BinaryPredicate>
			void unique(BinaryPredicate	binary_pred);

			void merge(list<T,Alloc>& x);

			template <class Compare> 
			void merge(list<T,Alloc>& x, Compare comp);
			
			void sort();

			template <class Compare>
			void sort(Compare comp);

			void reverse();
			};

			template <class T, class Alloc>
			bool operator==(const list<T,Alloc>& x, const list<T,Alloc>& y);
			template <class T, class Alloc>
			bool operator< (const list<T,Alloc>& x, const list<T,Alloc>& y);
			template <class T, class Alloc>
			bool operator!=(const list<T,Alloc>& x, const list<T,Alloc>& y);
			template <class T, class Alloc>
			bool operator> (const list<T,Alloc>& x, const list<T,Alloc>& y);
			template <class T, class Alloc>
			bool operator>=(const list<T,Alloc>& x, const list<T,Alloc>& y);
			template <class T, class Alloc>
			bool operator<=(const list<T,Alloc>& x, const list<T,Alloc>& y);
			
			template <class T, class Alloc>
			void swap(list<T,Alloc>& x, list<T,Alloc>& y);
}

#endif