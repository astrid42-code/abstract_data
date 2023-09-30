#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iostream>
#include <iterator>

// type traits for iterators 

namespace ft
{
	template<class T> 
	struct iterator_traits
	{
		public:

			typedef typename T::iterator_category	iterator_category; // §19.2.3
			typedef typename T::value_type 			value_type; // type of element
			typedef typename T::difference_type 	difference_type; // diff entre 2 iterators
			typedef typename T::pointer 			pointer; // return type of operator– >()
			typedef typename T::reference 			reference; // return type of operator*()
	};

	// specialisation for pointers types 
	template<typename T> 
	struct iterator_traits<T*>
	{
		public:

			typedef std::random_access_iterator_tag iterator_category;
			typedef T 								value_type;
			typedef std::ptrdiff_t 					difference_type;
			typedef T* 								pointer;
			typedef T& 								reference;
	};

	// specialisation for const pointers types 
	template<class T> 
	struct iterator_traits<const T*>
	{
		public:

			typedef std::random_access_iterator_tag 	iterator_category;
			typedef T 									value_type;
			typedef std::ptrdiff_t 						difference_type;
			typedef const T* 							pointer;
			typedef const T& 							reference;
	};

}

// https://cplusplus.com/reference/iterator/iterator/

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	class iterator
	{

		public:
			typedef Category							iterator_category;
			typedef T									value_type;
			typedef Distance							difference_type;
			typedef Pointer								pointer;
			typedef Reference							reference;
			typedef const Reference						const_reference;
			
	};
}

#endif