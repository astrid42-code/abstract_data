#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include "rev_it.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"


// A sequence is a kind of container that organizes a finite set of objects,
// all of the same type, into a strictly linear arrangement. 
// vector is the type of sequence that should be used by default

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			typedef typename Alloc::reference 				reference;
			typedef typename Alloc::const_reference 		const_reference;
			typedef T* 										iterator;
			typedef const T* 								const_iterator;
			typedef size_t 									size_type;
			typedef std::ptrdiff_t 							difference_type;
			typedef T 										value_type;
			typedef Alloc 									alloc_type;
			typedef typename Alloc::pointer 				pointer;
			typedef typename Alloc::const_pointer 			const_pointer;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			size_type 	_size; // nb of objects in my vector
			size_type 	_capacity; // total capacity of my vector (distance between first and last)
			Alloc		_alloc; // alloc object
			pointer		_begin; // ptr to begining of memory block
			
		
		public:

			// 23.2.4.1 construct/copy/destroy:

			explicit vector(const Alloc &alloc = Alloc()) : _size(0), _capacity(0), _alloc(alloc), _begin(NULL) { }
			
			explicit vector(size_type n, const T& value = T(), const Alloc& alloc = Alloc())
				: _size(n), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity)) 
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], value);
			}

			template <class _Iter>
			vector(_Iter first, typename ft::enable_if<!ft::is_integral<_Iter>::value, _Iter>::type last, const alloc_type& alloc = alloc_type())
						: _size(std::distance(first, last)), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity))
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], *(first++));
			}

			// copy constructor
			vector(const vector& x)
			{
				_capacity = x.size();
				_size = x.size();
				_alloc = x.get_allocator();
				_begin = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++){
					_alloc.construct(&_begin[i], x[i]);
				}
			}

			~vector()
			{
				clear();
				for (size_t i = 0; i < _size; i++){
					_alloc.destroy(&_begin[i]);
				}
				if (_begin != NULL)
					_alloc.deallocate(_begin, _capacity);
			}

			vector& operator=(const vector& x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return (*this);
			}

			// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			// https://cplusplus.com/reference/vector/vector/assign/
			// In the range version (1), the new contents are elements constructed from each of the elements in the range between first and last, in the same order.

			template <class _Iter>
			void assign(_Iter first, typename enable_if<!is_integral<_Iter>::value, _Iter>::type last)
			{
				difference_type diff = std::distance(first, last);
				if (_begin)
					clear();
				reserve(diff);
				insert(begin(), first, last);
				_size = diff;
			}
			
			// in the fill version (2), the new contents are n elements, each initialized to a copy of val.
			void assign(size_type n, const value_type &val)
			{
				if (_begin)
					clear();
				reserve(n);
				insert(begin(), n, val);
				_size = n;
			}

			// Get a copy of the container’s allocator
			// In all container types defined in this clause, the member
			// get_allocator() returns a copy of the Alloc object used to construct the container
			alloc_type get_allocator() const
			{
				return (_alloc);
			}

			// iterators:

			// begin() returns an iterator referring to the first element in the container. end() returns an iterator
			// which is the past-the-end value for the container. If the container is empty, then begin() == end();

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

			// 23.2.4.2 capacity:
			
			// The member function size() returns the number of elements in the container. Its semantics is defined by
			// the rules of constructors, inserts, and erases.
			size_type size() const
			{
				return (_size);
			}
			
			// Size of the largest possible container.
			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			// resize :
			// Change size of container

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

			// Returns: The total number of elements that the vector can hold without requiring reallocation
			// Space allocated for vector 
			size_type capacity() const
			{
				return _capacity;
			}
			
			// Is the container empty?
			bool empty() const 
			{
				return (_size == 0);
			}

			// Reserve space for future expansion

			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				else if (_capacity > n)
					return ;
				else
				{
					vector tmp = *this;
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

			// element access:
			reference operator[](size_type n)
			{
				return *(_begin + n);
			}

			const_reference operator[](size_type n) const
			{
				return *(_begin + n);
			}

			// reference at(size_type n) ;

			const_reference at(size_type n) const
			{
				if (n >= size())
					throw std::out_of_range("vector::at");
				else
					return (_begin[n]);
			}

			reference at(size_type n)
			{
				if (n >= size())
					throw std::out_of_range("vector::at");
				else
					return (_begin[n]);
			}

			// Returns a reference to the first element in the vector.
			reference front()
			{
				return *(_begin);
			}

			const_reference front() const
			{
				return *(_begin);
			}

			// Returns a reference to the last element in the vector.
			reference back()
			{
				return *(end() - 1);
			}

			const_reference back() const
			{
				return *(end() - 1);
			}

			// 23.2.4.3 modifiers:

			// if an exception is thrown by a push_back() or push_front() function, that function has no effects.

			// pushback : Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
			// This effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
			
			void push_back(const T& x)
			{
				if (_capacity == 0)
					reserve(1);
				else if (_size >= _capacity)
					reserve(_capacity * 2);
				_alloc.construct(&_begin[_size], x);
				_size++;
			}

			// no erase(), pop_back() or pop_front() function throws an exception
			void pop_back()
			{
				iterator it = end() - 1;
				erase(it);
			}

			// insert :
			// https://en.cppreference.com/w/cpp/container/vector/insert

			iterator insert(iterator pos, const value_type& val)
			{
				try
				{
					ft::vector<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
					size_type tmp_s = std::distance(begin(), pos);

					if (_size + 1 > _capacity)
						reserve(_size * 2);
					clear();

					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);
					push_back(val);
					for (iterator it2 = tmp_it; it2 != tmp_v.end(); it2++)
						push_back(*it2);

					return (&_begin[tmp_s]);
				}

				catch(const std::exception &e)
				{
					throw std::length_error("cannot create std::vector larger than max_size()");
				}
			}
			
			// insert fill
			void insert(iterator pos, size_type n, const value_type& val)
			{
				try
				{
					size_type s = _size + n; 
					size_type i = 0;
				
					ft::vector<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);

					if (n == 0)
						return;
					if (s > _capacity)
						reserve(std::max(s, _size * 2));
					clear();

					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);
					while (i != n)
					{
						push_back(val);
						i++;
					}

					for (iterator it2 = tmp_it; it2 != tmp_v.end(); it2++)
						push_back(*it2);
				}

				catch(const std::exception &e)
				{
					throw std::length_error("vector::_M_fill_insert");
				}
			}

			template <class _Iter>
			void insert(iterator pos, _Iter first, typename enable_if<!is_integral<_Iter>::value, _Iter>::type last)
			{
				try
				{
					size_type tmp2 = std::distance(first, last);
					size_type s = _size + tmp2;

					ft::vector<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
				
					if (s > _capacity){
						reserve(std::max(s, _size * 2));
					}
					clear();

					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);

					for (size_type i = 0; first != last; i++)
						push_back(*first++);
					for (iterator it2 = tmp_it; it2< tmp_v.end(); it2++)
						push_back(*it2);
				}

				catch(const std::exception &e){
					throw std::length_error("vector::_M_fill_insert"); 
				}
			}

			// erase:
			// Effects: Invalidates all the iterators and references after the point of the erase.
			
			iterator erase(iterator pos)
			{
				iterator _end = end();
				try
				{
					for (iterator it = pos; it < _end; it++)
					{
						_alloc.destroy(it);
						if (it + 1 != _end)
							_alloc.construct(it, *(it + 1));
					}
					_size--;
					return (pos);
				}
				catch (const std::exception& e)
				{
					throw "Error : erase";
				}
			}

			iterator erase(iterator first, iterator last)
			{
				if (first == last)
					return (first);
				else
				{
					difference_type diff = std::distance(first, last); 
					iterator it  = first;
					for (it = first; it <  end() - diff; it++)
					{
						_alloc.destroy(it);
						_alloc.construct(it, *(it + diff));
					}
					while (it != end())
					{
						_alloc.destroy(it);
						it++;
					}
					_size -= diff ;
					
				}
				return (first);
				
			}

			void swap(vector & y)
			{
				size_t	tmp_capacity = y._capacity;
				size_t	tmp_size = y._size;
				Alloc	tmp_alloc = y._alloc;
				pointer	tmp_begin = y._begin;

				y._capacity = _capacity;
				y._size = _size;
				y._alloc = _alloc;
				y._begin = _begin;

				_capacity = tmp_capacity;
				_size = tmp_size;
				_alloc = tmp_alloc;
				_begin = tmp_begin;
			}

			void clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_begin[i]);
				_size = 0;
			}

		};

	// Is the content of two containers the same?
	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y)
	{
		return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
	}
	
	// Is the content of two containers different?
	template <class T, class Alloc>
	bool operator!=(const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y)
	{
		return !(x == y);
	}
	
	// Is one container lexicographically before another ?
	template <class T, class Alloc>
	bool operator< (const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
	
	template <class T, class Alloc>
	bool operator> (const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y)
	{
		return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
	}
	
	template <class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y)
	{
		return !(x < y);
	}
	
	template <class T, class Alloc>
	bool operator<=(const ft::vector<T,Alloc>& x, const ft::vector<T,Alloc>& y)
	{
		return (!(x > y));
	}

	// specialized algorithms:
	// Swap elements of two containers

	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif