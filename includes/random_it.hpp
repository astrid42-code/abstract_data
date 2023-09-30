#ifndef IT_HPP
#define IT_HPP

#include <iterator>
#include "iterator_traits.hpp"


// https://cplusplus.com/reference/iterator/RandomAccessIterator/

namespace ft
{
	template<class Iterator> 
	class random_it : ft::iterator<std::random_iterator_tag, Iterator>
	{
		public:
			typedef _Iter 																					iterator;
			typedef typename 	ft::iterator<std::random_iterator_tag, _Iter>::iterator_category 	iterator_category;
			typedef typename 	ft::iterator<std::random_iterator_tag, _Iter>::value_type 			value_type;
			typedef typename 	ft::iterator<std::random_iterator_tag, _Iter>::difference_type		difference_type;
			typedef typename 	ft::iterator<std::random_iterator_tag, _Iter>::pointer 				pointer;
			typedef typename 	ft::iterator<std::random_iterator_tag, _Iter>::reference 			reference;

checker les operations manquantes et / ou a modifier par rapport aux biderectional

			// constructors/destructor

			random_it() : _current() {}

			explicit random_it(iterator x) : _current(x) {}

			random_it(const random_it &x) {
				_current = x._current;
			}

			template<class Other>
			random_it(const random_it<Other> & x) : _current(x._current) {}

			~random_it() {}

			template<class U>
			random_it & operator=(const random_it<U> &op)
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
			random_it& operator++() 
			{
				++_current; // ou --?
				return *this;
			}

			random_it operator++(int)
			{
				random_it tmp = *this;
				++(*this);
				return tmp;
			}

			random_it& operator--()
			{
				--_current;
				return *this;
			}

			random_it operator--(int)
			{
				random_it tmp = *this;
				--(*this);
				return tmp;

			}

			bool	operator==(const random_it &it) const
			{
				return (_current == it._current);
			}

			bool	operator!=(const random_it &it) const
			{
				return !(*this == it);
			}

			operator random_it<const value_type>() const 
			{
				return (random_it<const value_type>(_current));
			};
		
		private:
			pointer	ptr;
	};
	
	// random_it::random_it(/* args */)
	// {
	// }
	
	// random_it::~random_it()
	// {
	// }
	
	
	// struct iterator_traits;
	// template<class T> struct iterator_traits<T*>;

	// template<class Category, class T, class Distance = ptrdiff_t,
	// 	class Pointer = T*, class Reference = T&> struct iterator;

	// struct input_iterator_tag {};
	// struct output_iterator_tag {};
	// struct forward_iterator_tag: public input_iterator_tag {};
	// struct bidirectional_iterator_tag: public forward_iterator_tag {};
	// struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	// // 24.3.4, iterator operations:
	// template <class InputIterator, class Distance>
	// 	void advance(InputIterator& i, Distance n);

	// template <class InputIterator>
	// 	typename iterator_traits<InputIterator>::difference_type
	// 	distance(InputIterator first, InputIterator last);

	// // 24.4, predefined iterators:
	// template <class Iterator> class reverse_iterator;

	// template <class Iterator>
	// 	bool operator==(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);

	// template <class Iterator>
	// 	bool operator<(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);

	// template <class Iterator>
	// 	bool operator!=(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);
	
	// template <class Iterator>
	// 	bool operator>(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);
	
	// template <class Iterator>
	// 	bool operator>=(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);
	
	// template <class Iterator>
	// 	bool operator<=(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);
	
	// template <class Iterator>
	// 	typename reverse_iterator<Iterator>::difference_type operator-(
	// 		const reverse_iterator<Iterator>& x,
	// 		const reverse_iterator<Iterator>& y);
	
	// template <class Iterator>
	// 	reverse_iterator<Iterator>
	// 		operator+(
	// 			typename reverse_iterator<Iterator>::difference_type n,
	// 			const reverse_iterator<Iterator>& x);
	
	// template <class Container> class back_insert_iterator;
	// template <class Container>
	// 	back_insert_iterator<Container> back_inserter(Container& x);
	
	// template <class Container> class front_insert_iterator;
	// template <class Container>
	// 	front_insert_iterator<Container> front_inserter(Container& x);
	
	// template <class Container> class insert_iterator;
	// template <class Container, class Iterator>
	// 	insert_iterator<Container> inserter(Container& x, Iterator i);
	
	// // 24.5, stream iterators:
	// template <class T, class charT = char, class traits = char_traits<charT>,
	// 			class Distance = ptrdiff_t>
	// class istream_iterator;
	// template <class T, class charT, class traits, class Distance>
	// 	bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
	// 		const istream_iterator<T,charT,traits,Distance>& y);
	
	// template <class T, class charT, class traits, class Distance>
	// 	bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
	// 		const istream_iterator<T,charT,traits,Distance>& y);
	
	// template <class T, class charT = char, class traits = char_traits<charT> >
	// 	class ostream_iterator;
	
	// template<class charT, class traits = char_traits<charT> >
	// 	class istreambuf_iterator;
	
	// template <class charT, class traits>
	// 	bool operator==(const istreambuf_iterator<charT,traits>&a,
	// 				const istreambuf_iterator<charT,traits>&b);
	
	// template <class charT, class traits>
	// 	bool operator!=(const istreambuf_iterator<charT,traits>&a,
	// 				const istreambuf_iterator<charT,traits>&b);
	
	// template <class charT, class traits = char_traits<charT> >
	// 	class ostreambuf_iterator;

}


#endif
