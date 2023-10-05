#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <iostream>
#include <string>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rev_it.hpp"

// A sequence is a kind of container that organizes a finite set of objects,
// all of the same type, into a strictly linear arrangement. 
// deque is the data structure of choice when most insertions and deletions
// take place at the beginning or at the end of the sequence


namespace ft 
{

	template <class T, class Alloc = std::allocator<T> >
	class deque {
		public:
			// types:
			typedef typename Alloc::reference 				reference;
			typedef typename Alloc::const_reference 		const_reference;
			typedef T* 										iterator;
			typedef const T* 								const_iterator;
			typedef size_t 									size_type;
			typedef std::ptrdiff_t 							difference_type;
			typedef T 										value_type;
			typedef Alloc 									allocator_type;
			typedef typename Alloc::pointer 				pointer;
			typedef typename Alloc::const_pointer 			const_pointer;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

		private:
			size_type 	_size; // nb of objects in my deque
			size_type 	_capacity; // total capacity of my deque (distance between first and last)
			Alloc		_alloc; // alloc object
			pointer		_begin; // ptr to begining of memory block

		public:

			// 23.2.1.1 construct/copy/destroy:

			// Effects: Constructs an empty deque, using the specified allocator.
			// Complexity: Constant.
			explicit deque(const Alloc &alloc = Alloc()) : _size(0), _capacity(0), _alloc(alloc), _begin(NULL) {}

			// Effects: Constructs a deque with n copies of value, using the specified allocator.
			// Complexity: Linear in n.
			explicit deque(size_type n, const T & value = T(), const Alloc& alloc = Alloc())
				: _size(n), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity))
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], value);
			}

			// Effects: Constructs a deque equal to the range [first,last), using the specified allocator.
			// Complexity: If the iterators first and last are forward iterators, bidirectional iterators, or random
			// access iterators the constructor makes only N calls to the copy constructor, and performs no realloca-
			// tions, where N is last - first. It makes at most N calls to the copy constructor of T and log N reallocations
			// if they are input iterators.
			template <class Iter>
			deque(Iter first, typename ft::enable_if<!ft::is_integral<Iter>::value, Iter>::type last, const allocator_type& alloc = Alloc())
				: _size(std::distance(first, last)), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity))
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], *(first++));
			}

			// copy constructor
			deque(const deque<T,Alloc>& x)
			{
				_capacity = x.size();
				_size = x.size();
				_alloc = x.get_allocator();
				_begin = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++){
					_alloc.construct(&_begin[i], x[i]);
				}
			}
			
			~deque(){
				clear();
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.destroy(&_begin[i]);
				}
				if (_begin != NULL)
					_alloc.deallocate(_begin, _capacity);
			}
			
			deque<T,Alloc>& operator=(const deque<T,Alloc>& x);
			
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			
			void assign(size_type n, const T& t);
			
			allocator_type get_allocator() const
			{
				return(_alloc);
			}
			
			// iterators:
			iterator begin()
			{
				return iterator(_begin);
			}

			const_iterator begin() const
			{
				return const_iterator(_begin);
			}
			
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			
			// 23.2.1.2 capacity:
			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const;
			void resize(size_type sz, T c = T());
			bool empty() const;

			// element access:
			reference operator[](size_type n)
			{
				return *(_begin + n);
			}

			const_reference operator[](size_type n) const
			{
				return *(_begin + n);
			}

			reference at(size_type n);
			const_reference at(size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			// 23.2.1.3 modifiers:
			void push_front(const T& x);
			void push_back(const T& x);
			iterator insert(iterator position, const T& x);
			void insert(iterator position, size_type n, const T& x);
			template <class InputIterator>
			void insert (iterator position,
			InputIterator first, InputIterator last);
			void pop_front();
			void pop_back();
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(deque<T,Alloc>&);

			void clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_begin[i]);
				_size = 0;
			}

	};
    
	template <class T, class Alloc>
	bool operator==(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y);
    
	template <class T, class Alloc>
	bool operator<(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y);

	template <class T, class Alloc>
	bool operator!=(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y);

	template <class T, class Alloc>
	bool operator>(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y);

	template <class T, class Alloc>
	bool operator>=(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y);

	template <class T, class Alloc>
	bool operator<=(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y);

	// specialized algorithms:
	template <class T, class Alloc>
	void swap(ft::deque<T,Alloc>& x, ft::deque<T,Alloc>& y);
}

#endif