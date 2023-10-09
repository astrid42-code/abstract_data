#ifndef P_QUEUE_HPP
#define P_QUEUE_HPP

#include <iostream>
#include <deque>
#include <queue>
#include <vector>


namespace ft 
{
	template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
	class priority_queue 
	{
		public:
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef Container container_type;

		protected:
			Container c;
			Compare comp;

		public:

			// Requires:
			// x defines a strict weak ordering (25.3).
			// Effects: Initializes comp with x and c with y; calls make_heap(c.begin(), c.end(), comp)
			explicit priority_queue(const Compare& x = Compare(), const Container& ctn = Container()) : c(ctn)
			{
				std::cout << "prout\n";
			}
			
			template <class InputIterator>
			priority_queue(InputIterator first, InputIterator last, const Compare& x = Compare(), const Container& = Container())
			{
				std::cout << "prout2\n";
			}
			
			bool empty() const 
			{ return c.empty(); }
			
			size_type size() const 
			{ return c.size(); }
			
			const value_type& top() const 
			{ return c.front(); }
			
			// Effects:
			// c.push_back(x);
			// push_heap(c.begin(), c.end(), comp);
			void push(const value_type& x)
			{
				c.push_back(x);
				push_heap(c.begin(), c.end(), comp);
			}
			
			void pop()
			{
				pop_heap(c.begin(), c.end(), comp);
				c.pop_back();
			}
	};
	// no equality is provided
}




#endif