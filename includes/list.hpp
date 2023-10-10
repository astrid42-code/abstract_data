#ifndef list_HPP
#define list_HPP

#include <iostream>
#include <string>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rev_it.hpp"
#include "bi_directional_it.hpp"
#include "node_list.hpp"

// A sequence is a kind of container that organizes a finite set of objects,
// all of the same type, into a strictly linear arrangement. 
// list should be used when there are frequent insertions and deletions 
// from the middle of the sequence.

// A list is a linked list, meaning data which are linked together by pointers.
// You have constant-time access to the beginning and the end, 
// but in order to get anywhere in the middle you need to iterate through the list.
// You can add elements anywhere in the list in constant time, though,
// if you already have a pointer to one of the nearby nodes.

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
			// Reserve space for future expansion

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("deque::reserve");
				else if (_capacity > n)
					return ;
				else
				{
					deque tmp = *this;
					size_type old_size = _size;
					size_type old_capacity = _capacity;
					pointer old_begin = _begin;
					clear();
					_capacity = n;
					if (_capacity)
						_begin = _alloc.allocate(_capacity);
					_size = old_size;

					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(&_begin[i], tmp[i]);
					}
					_alloc.deallocate(old_begin, old_capacity);
				}
			}
			
		
			public:

			// 23.2.2.1 construct/copy/destroy:
			explicit list(const Alloc &alloc = Alloc()) : _size(0), _capacity(0), _alloc(alloc), _begin(NULL) { }
			
			explicit list(size_type	n, const T&	value = T(), const Alloc& alloc = Alloc())
				: _size(n), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity)) 
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], value);
			}
			
			template <class Iter>
			list(Iter first, typename ft::enable_if<!ft::is_integral<Iter>::value, Iter>::type last, const Alloc& = Alloc())
				: _size(std::distance(first, last)), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity))
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], *(first++));
			}

			list(const list<T,Alloc>& x)
			{
				_capacity = x.size();
				_size = x.size();
				_alloc = x.get_allocator();
				_begin = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++){
					_alloc.construct(&_begin[i], x[i]);
				}
			}

			~list()
			{
				clear();
				for (size_t i = 0; i < _size; i++){
					_alloc.destroy(&_begin[i]);
				}
				if (_begin != NULL)
					_alloc.deallocate(_begin, _capacity);
			}

			list<T,Alloc>& operator=(const list<T,Alloc>& x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return (*this);
			}

			template <class Iter>
			void assign(Iter first, Iter last);

			void assign(size_type n, const T& t);
			alloc_type get_allocator() const;

			// iterators:
			iterator begin() 
			{
				return iterator(_begin);
			}

			const_iterator begin() const 
			{
				return const_iterator(_begin);
			}

			iterator end() 
			{
				return (_begin + _size); 
			}

			const_iterator end() const 
			{
				return (_begin + _size);
			}
			
			reverse_iterator rbegin() 
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const 
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}


			// 23.2.2.2 capacity:
			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			void resize(size_type sz, T c = T())
			{
				if (sz > _size)
				{
					reserve(std::max(_size * 2, sz));
					while (_size < sz)
					{
						_alloc.construct(&_begin[_size], c);
						_size++;
					}
					_size = sz;
				}
				else if (sz < _size)
				{
					while (sz < _size)
					{
						_alloc.destroy(&_begin[_size - 1]);
						_size--;
					}
				_size = sz;
				}
				else
					return ;
			}
// 			if (sz > size())
			// insert(end(), sz-size(), c);
			// else if (sz < size())
			// erase(begin()+sz, end());
			// else
			// ;

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