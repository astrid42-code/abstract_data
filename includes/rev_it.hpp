#ifndef REV_IT_HPP
#define REV_IT_HPP

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
	template <typename _Iter>
	
	class reverse_iterator
	{
		private:
			_Iter 								_current; // _current points to the element after the one *this refers to.
			typedef ft::iterator_traits<_Iter>	_iterator_traits;
		
		public:
			typedef _Iter 												_iterator;
			typedef typename 	_iterator_traits::iterator_category 	_iterator_category;
			typedef typename 	_iterator_traits::difference_type		_difference_type;
			typedef typename 	_iterator_traits::pointer 				_pointer;
			typedef typename 	_iterator_traits::reference 			_reference;

			// default constructor
			reverse_iterator() : _current() { }
			
			// initalization constructor
			explicit reverse_iterator(_iterator x) : _current(x) { }
			
			// copy / type-cast constructor
			reverse_iterator(const reverse_iterator &x ) : _current(x._current) { }
			
			template<class Other> 
				reverse_iterator(const reverse_iterator<Other>& x) : _current(x.base()) { }
			
			~reverse_iterator() {}

			template<class U>
			reverse_iterator & operator=(const reverse_iterator<U> & op)
			{
				_current = op.base();
				return (*this);
			}
			
			// base : accesses the underlying iterator 
			_iterator base() const
			{
				return _current;
			}

			// ' * ' to access the one-before element that we are _currently pointing to.
			_reference operator*() const
			{
				_iterator tmp = _current;
				return (*--tmp);
			}
					
			// ' -> ' return the address returned by the operator ' * ' 
			// - the one-before element that we are _currently pointing to.
			_pointer operator->() const
			{
				return &(operator*());
			}
			
			// [] : accesses an element by index 
			_reference operator[](_difference_type n) const
			{
				return base()[-n - 1];
			}
			
			// advances or decrements the iterator 
			reverse_iterator& operator++()
			{
				--_current;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator t = *this;
				++(*this);
				return t;
			}

			reverse_iterator& operator--()
			{
				++_current;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator t = *this;
				--(*this);
				return t;
			}
			
			reverse_iterator operator+(_difference_type n) const
			{
				reverse_iterator tmp(*this);
				tmp._current -= n;
				return (tmp);
			}

			reverse_iterator operator-(_difference_type n) const
			{
				reverse_iterator tmp(*this);
				tmp._current += n;
				return (tmp);
			}
			
			_difference_type operator-(reverse_iterator const &n)
			{
				_difference_type tmp = n._current - _current;
				return (tmp);
			}

			reverse_iterator& operator+=(_difference_type const n)
			{
				_current -= n;
				return (*this);
			}
			
			reverse_iterator& operator-=(_difference_type const &n)
			{
				_current += n;
				return (*this);
			}
				
	};
	
	// non members functions (logical operators)
	
	// compares the underlying iterators
	template <class _Iter>
	bool operator==(const ft::reverse_iterator<_Iter>& lhs, const ft::reverse_iterator<_Iter>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator==(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	
	template <class _Iter>
	bool operator!=(const ft::reverse_iterator<_Iter>& lhs, const ft::reverse_iterator<_Iter>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator!=(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	
	template <class _Iter>
	bool operator<(const ft::reverse_iterator<_Iter>& lhs, const ft::reverse_iterator<_Iter>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator<(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class _Iter>
	bool operator<=(const ft::reverse_iterator<_Iter>& lhs, const ft::reverse_iterator<_Iter>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator<=(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class _Iter>
	bool operator>(const ft::reverse_iterator<_Iter>& lhs, const ft::reverse_iterator<_Iter>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator>(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class _Iter>
	bool operator>=(const ft::reverse_iterator<_Iter>& lhs, const ft::reverse_iterator<_Iter>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator>=(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename _Iter>
    typename reverse_iterator<_Iter>::_difference_type
    operator-(const reverse_iterator<_Iter>& __x,
              const reverse_iterator<_Iter>& __y)
    {
        return __y.base() - __x.base();
    }

	template<typename _Iter>
    typename reverse_iterator<_Iter>::_difference_type
    operator+(const reverse_iterator<_Iter>& __x,
              const reverse_iterator<_Iter>& __y)
    {
        return __y.base() + __x.base();
    }
		
	template<typename _IteratorL, typename _IteratorR>
   typename reverse_iterator<_IteratorL>::_difference_type
    operator+(const reverse_iterator<_IteratorL>& __x,
              const reverse_iterator<_IteratorR>& __y)
    {
        return __y.base() + __x.base();
    }

	template<typename _Iter>
	reverse_iterator<_Iter>
    operator+(typename reverse_iterator<_Iter>::_difference_type __n, const reverse_iterator<_Iter>& __x)
    {
		return reverse_iterator<_Iter>(__x.base() - __n);
	}


	template<typename _Iter>
	reverse_iterator<_Iter>
    operator-(typename reverse_iterator<_Iter>::_difference_type __n, const reverse_iterator<_Iter>& __x)
    {
		return reverse_iterator<_Iter>(__x.base() + __n);
	}
	
}

#endif


// https://en.cppreference.com/w/cpp/iterator/reverse_iterator

// logical operators : https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_cmp



