#ifndef BI_DIRECTIONAL_IT_HPP
#define BI_DIRECTIONAL_IT_HPP

#include <iostream>
#include <iterator>
#include "iterator_traits.hpp"

// map iterators with a pair (key and value)
// https://cplusplus.com/reference/iterator/

namespace ft{
	template< class _Iter >
    class bidirectional_iterator_tag : ft::iterator<std::bidirectional_iterator_tag, _Iter>
    {
		private:
			_Iter 								_current; // _current points to the element after the one *this refers to.
			typedef ft::iterator_traits<_Iter>	_iterator_traits;
		
		public:
			typedef _Iter 																					iterator;
			typedef typename 	ft::iterator<std::bidirectional_iterator_tag, _Iter>::iterator_category 	iterator_category;
			typedef typename 	ft::iterator<std::bidirectional_iterator_tag, _Iter>::value_type 			value_type;
			typedef typename 	ft::iterator<std::bidirectional_iterator_tag, _Iter>::difference_type		difference_type;
			typedef typename 	ft::iterator<std::bidirectional_iterator_tag, _Iter>::pointer 				pointer;
			typedef typename 	ft::iterator<std::bidirectional_iterator_tag, _Iter>::reference 			reference;

			// constructors/destructor

			bidirectional_iterator_tag() : _current() {}

			explicit bidirectional_iterator_tag(iterator x) : _current(x) {}

			bidirectional_iterator_tag(const bidirectional_iterator_tag &x) {
				_current = x._current;
			}

			template<class Other>
			bidirectional_iterator_tag(const bidirectional_iterator_tag<Other> & x) : _current(x._current) {}

			~bidirectional_iterator_tag() {}

			template<class U>
			bidirectional_iterator_tag & operator=(const bidirectional_iterator_tag<U> &op)
			{
				if (*this == op)
					return (*this);
				_current = op.base();
				return (*this);
			}

			iterator	base() const 
			{
				return (_current);
			}

			// operators 

			// This can be dereferenced. We can use the dereference operator (*) to get value.
			reference operator*() const 
			{
				return (*_current);
			}
			
			// 'The mutable iterator can be dereferenced as lvalue
			pointer operator->() const 
			{
				return (&(operator*()));
			}
			
			// [] : accesses an element by index 
			reference operator[](const difference_type n) const 
			{
				return (base()[-n - 1]);
			} 
			
			// advances or decrements the iterator 
			bidirectional_iterator_tag& operator++() 
			{
				++_current; // ou --?
				return *this;
			}

			bidirectional_iterator_tag operator++(int)
			{
				bidirectional_iterator_tag tmp = *this;
				++(*this);
				return tmp;
			}

			bidirectional_iterator_tag& operator--()
			{
				--_current;
				return *this;
			}

			bidirectional_iterator_tag operator--(int)
			{
				bidirectional_iterator_tag tmp = *this;
				--(*this);
				return tmp;

			}

			bool	operator==(const bidirectional_iterator_tag &it) const
			{
				return (_current == it._current);
			}

			bool	operator!=(const bidirectional_iterator_tag &it) const
			{
				return !(*this == it);
			}

			operator bidirectional_iterator_tag<const value_type>() const 
			{
				return (bidirectional_iterator_tag<const value_type>(_current));
			};
    };

		// non members functions (logical operators)
	
		// compares the underlying iterators
		template <class _Iter>
		bool operator==(const ft::bidirectional_iterator_tag<_Iter>& lhs, const ft::bidirectional_iterator_tag<_Iter>& rhs)
		{
			return (lhs== rhs);
		}

		template <class _Iter1, class _Iter2>
		bool operator==(const ft::bidirectional_iterator_tag<_Iter1>& lhs, const ft::bidirectional_iterator_tag<_Iter2>& rhs)
		{
			return (lhs.base() == rhs.base());
		}
		
		template <class _Iter>
		bool operator!=(const ft::bidirectional_iterator_tag<_Iter>& lhs, const ft::bidirectional_iterator_tag<_Iter>& rhs)
		{
			return (lhs != rhs);
		}

		template <class _Iter1, class _Iter2>
		bool operator!=(const ft::bidirectional_iterator_tag<_Iter1>& lhs, const ft::bidirectional_iterator_tag<_Iter2>& rhs)
		{
			return (lhs.base() != rhs.base());
		}
}

#endif
