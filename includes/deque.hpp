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
			explicit deque(const Alloc &alloc = Alloc()) : _size(0), _capacity(0), _alloc(alloc), _begin(NULL) 
			{
				// std::cout << "default constructor" << std::endl;
			}

			// Effects: Constructs a deque with n copies of value, using the specified allocator.
			// Complexity: Linear in n.
			explicit deque(size_type n, const T & value = T(), const Alloc& alloc = Alloc())
				: _size(n), _capacity(_size), _alloc(alloc), _begin(_alloc.allocate(_capacity))
			{
				// std::cout << "constructor 2" << std::endl;
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
				// std::cout << "constructor 3" << std::endl;
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_begin[i], *(first++));
			}

			// copy constructor
			deque(const deque<T,Alloc>& x)
			{
				// std::cout << "copy constructor" << std::endl;
				_capacity = x.size();
				_size = x.size();
				_alloc = x.get_allocator();
				_begin = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++){
					_alloc.construct(&_begin[i], x[i]);
				}
			}
			
			~deque(){
				// std::cout << "destructor" << std::endl;
				clear();
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.destroy(&_begin[i]);
				}
				if (_begin != NULL)
					_alloc.deallocate(_begin, _capacity);
			}
			
			deque<T,Alloc>& operator=(const deque<T,Alloc>& x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return (*this);
			}
			
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
			
			// 23.2.1.2 capacity:
			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			void resize(size_type sz, T c = T())
			// plus le droit a reserve!!!
			{
					if (sz > _size)
					{
						// reserve(std::max(_size * 2, sz));
						// _size++;
						size_type n = std::max(_size * 2, sz);
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

							for (size_type i = 0; i < _size; i++){
								_alloc.construct(&_begin[i], tmp[i]);
							}
							_alloc.deallocate(old_begin, old_capacity);
						}

						while (_size < sz)
						{
							// std::cout << "sz=" << _size << std::endl;
							_alloc.construct(&_begin[_size], c);
							_size++;
						}
						// std::cout << "sz = "<< sz << " size = "<< size() << std::endl;
						_size = sz;
					}
					else if (sz < _size)
					{
						// std::cout << "salut2" << std::endl;
						while (sz < _size)
						{
							_alloc.destroy(&_begin[_size - 1]);
							_size--;
						}
					_size = sz;
					}
					else
						return ;
				// 
				// if (sz > size())
				// {
				// 	insert(end(), sz - size(), c);
				// }
				// else if (sz < size())
				// {
				// 	std::cout << "salut2" << std::endl;
				// 	erase(begin() + sz, end());
				// }
				// return;
			}

			bool empty() const
			{
				return (_size == 0);
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

			reference at(size_type n);
			const_reference at(size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			// 23.2.1.3 modifiers:
			void push_front(const T& x);

			void push_back(const T& x)
			{
				// std::cout << "cap = " << _capacity << "sz = " << _size << std::endl;
				if (_capacity == 0)
				{
					// std::cout << "coucou1" << std::endl;
					// reserve(1);
					size_type n = 1;
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
				else if (_size >= _capacity){

					// std::cout << "coucou2" << std::endl;
					// reserve(_capacity * 2);
					size_type n = _capacity * 2;
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
				// std::cout << "coucou3" << std::endl;
				_alloc.construct(&_begin[_size], x);
				_size++;
			}

			iterator insert(iterator pos, const T& x)
			{
				try
				{
					ft::deque<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
					size_type tmp_s = std::distance(begin(), pos);

					if (_size + 1 > _capacity)
						// reserve(_size * 2);
					{
						size_type n = _size * 2;
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
					clear();

					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);
					push_back(x);
					for (iterator it2 = tmp_it; it2 != tmp_v.end(); it2++)
						push_back(*it2);

					return (&_begin[tmp_s]);
				}

				catch(const std::exception &e)
				{
					throw std::length_error("cannot create std::deque larger than max_size()");
				}
			}

			void insert(iterator pos, size_type n, const T& x)
			{
				try
				{
					size_type s = _size + n; 
					size_type i = 0;
				
					ft::deque<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
					if (n == 0)
						return;
					if (s > _capacity)
						// reserve(std::max(s, _size * 2));
					{
						size_type n = std::max(s, _size * 2);
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
					
					clear();

					for (iterator it2 = tmp_v.begin(); it2 != tmp_it; it2++)
						push_back(*it2);
					while (i != n)
					{
						push_back(x);
						i++;
					}

					for (iterator it2 = tmp_it; it2 != tmp_v.end(); it2++)
						push_back(*it2);
				}

				catch(const std::exception &e)
				{
					throw std::length_error("deque::_M_fill_insert");
				}
			}

			template <class Iter>
			void insert (iterator pos, Iter first, typename enable_if<!is_integral<Iter>::value, Iter>::type last)
			{
				try
				{
					size_type tmp2 = std::distance(first, last);
					size_type s = _size + tmp2;

					ft::deque<value_type>	tmp_v = *this;
					iterator tmp_it = tmp_v.begin() + std::distance(begin(), pos);
				
					if (s > _capacity){
						// reserve(std::max(s, _size * 2));
					{
						size_type n = std::max(s, _size * 2);
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
					throw std::length_error("deque::_M_fill_insert"); 
				}
			}

			void pop_front();
			void pop_back();
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

			void swap(deque<T,Alloc>& y)
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
    
	template <class T, class Alloc>
	bool operator==(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y)
	{
		return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y)
	{
		return !(x == y);
	}
    
	template <class T, class Alloc>
	bool operator<(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class T, class Alloc>
	bool operator>(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y)
	{
		return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
	}

	template <class T, class Alloc>
	bool operator>=(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y)
	{
		return !(x < y);
	}

	template <class T, class Alloc>
	bool operator<=(const ft::deque<T,Alloc>& x, const ft::deque<T,Alloc>& y)
	{
		return (!(x > y));
	}

	// specialized algorithms:
	template <class T, class Alloc>
	void swap(ft::deque<T,Alloc>& x, ft::deque<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif