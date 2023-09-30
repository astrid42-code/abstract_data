#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <iostream>
#include <iomanip>

// is_integral :
// Checks whether T is an integral type. Provides the member constant value which is equal to true, 
// if T is the type bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, 
// or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. Otherwise, value is equal to false.

// enable_if (other type generator des type_traits > "Enable type if condition is met")
// If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.

namespace ft
{
	template<bool B, typename T = void>
	struct enable_if {};

	template <class T> // specialisation
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<signed char>
	{
		static const bool value = true; 
	};
	template <>
	struct is_integral<short int>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<long int>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true; 
	};

	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true; 
	};

	// lexicographical_compare:
	// https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
	// Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).

	// Elements are compared using operator<.
	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 )
	{
		for ( ; (first1 != last1); ++first1, ++first2 )
		{
			if (first2 == last2 || *first2 < *first1 ) 
				return false;
			if (*first1 < *first2) 
				return true;
		}
		return (first2 != last2);
	}

	// Elements are compared using the given binary comparison function comp.
	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp )
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// equal :
	// https://en.cppreference.com/w/cpp/algorithm/equal
	// Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise.

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, 
            InputIt2 first2 )
	{
    	for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
    	}
    	return true;
	}

	// Returns true if the range [first1, last1) is equal to the range [first2, last2), and false otherwise.
	template< class InputIt1, class InputIt2, class Compare >
	bool equal( InputIt1 first1, InputIt1 last1, 
           InputIt2 first2, Compare comp )
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!comp(*first1, *first2))
				return false;
		}
		return true;
	}
}

#endif