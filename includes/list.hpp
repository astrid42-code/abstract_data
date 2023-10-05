#ifndef list_HPP
#define list_HPP

#include <iostream>
#include <string>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rev_it.hpp"

// A sequence is a kind of container that organizes a finite set of objects,
// all of the same type, into a strictly linear arrangement. 
// list should be used when there are frequent insertions and deletions 
// from the middle of the sequence.


namespace ft 
{
	template <class T, class Allocator = std::allocator<T> > class list;
	template <class T, class Allocator>
	bool operator==(const list<T,Allocator>& x, const list<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator< (const list<T,Allocator>& x, const list<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator!=(const list<T,Allocator>& x, const list<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator> (const list<T,Allocator>& x, const list<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator>=(const list<T,Allocator>& x, const list<T,Allocator>& y);
	template <class T, class Allocator>
	bool operator<=(const list<T,Allocator>& x, const list<T,Allocator>& y);
	template <class T, class Allocator>
	void swap(list<T,Allocator>& x, list<T,Allocator>& y);
}

#endif