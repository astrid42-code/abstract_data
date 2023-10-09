#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <deque>
// #include "deque.hpp"

namespace ft 
{
	template <class T, class Container = std::deque<T> > // a modifier avec ft::deque quand termine
	class queue 
	{
		private:
			// using "friend" keyword : 
			// authorize access to protected objects for non member functions
			// A friend class can access both private and protected members of the class in which it has been declared as friend.
			template <typename _T, typename _Container>
			friend bool operator==(const stack<_T, _Container>& x,
				const stack<_T, _Container>& y);

			template <typename _T, typename _Container>
			friend bool operator< (const stack<_T, _Container>& x,
				const stack<_T, _Container>& y);

			template <typename _T, typename _Container>
			friend bool operator!= (const stack<_T, _Container>& x,
				const stack<_T, _Container>& y);

			template <typename _T, typename _Container>
			friend bool operator> (const stack<_T, _Container>& x,
				const stack<_T, _Container>& y);

			template <typename _T, typename _Container>
			friend bool operator>= (const stack<_T, _Container>& x,
				const stack<_T, _Container>& y);
			
			template <typename _T, typename _Container>
			friend bool operator<= (const stack<_T, _Container>& x,
				const stack<_T, _Container>& y);

		public:
			typedef typename 	Container::value_type	value_type;
			typedef typename 	Container::size_type	size_type;
			typedef 			Container				container_type;
		
		protected:
			Container _c;
		
		public:
			explicit queue(const Container& ctn = Container()) : _c(ctn)
			{
				// std::cout << " TEST FT " << std::endl;
			}

			bool empty() const 
			{ 
				return _c.empty();
			}

			size_type size() const 
			{ 
				return _c.size();
			}

			value_type& front() 
			{
				return _c.front();
			}

			const value_type& front() const 
			{
				return _c.front();
			}

			value_type& back()
			{
				return _c.back();
			}

			const value_type& back() const
			{
				return _c.back();
			}

			void push(const value_type& x)
			{
				_c.push_back(x);
			}

			void pop()
			{
				_c.pop_front();
			}

	};

	template <class T, class Container>
	bool operator==(const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return (x._c == y._c);
	}

	template <class T, class Container>
	bool operator< (const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return (x._c < y._c);
	}

	template <class T, class Container>
	bool operator!=(const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return (x._c != y._c);
	}

	template <class T, class Container>
	bool operator> (const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return (x._c > y._c);
	}

	template <class T, class Container>
	bool operator>=(const queue<T, Container>& x, const queue<T, Container>& y)
	{
			return (x._c >= y._c);
	}

	template <class T, class Container>
	bool operator<=(const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return (x._c <= y._c);
	}
}


#endif
