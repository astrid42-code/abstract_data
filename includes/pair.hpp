#ifndef PAIR_HPP
#define PAIR_HPP

//std::pair is a class template that provides a way to store two heterogeneous objects as a single unit.

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		public:
			typedef T1  first_type;
			typedef T2  second_type;
			first_type  first;
			second_type second;

			// Default constructor. Value-initializes both elements of the pair, first and second.
			pair() : first(first_type()), second(second_type()) {}

			// Initializes first with x and second with y.
			pair( const T1& x, const T2& y ) : first(x), second(y) {}

			//  Initializes first with p.first and second with p.second.
			// p	-	pair of values used to initialize both elements of this pair
			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

			~pair() {}

			// Copy assignment operator. Replaces the contents with a copy of the contents of other.
			pair& operator=( const pair& other )
			{
				first = other.first;
				second = other.second;
				return (*this);
			}
	};

	// Tests if both elements of lhs and rhs are equal, that is, 
	// compares lhs.first with rhs.first and lhs.second with rhs.second.

	// return value : true if both lhs.first == rhs.first and lhs.second == rhs.second, otherwise false
	template< class T1, class T2 >
	bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) 
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	// return value : !(lhs == rhs)
	template< class T1, class T2 >
	bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(lhs == rhs);
	}

	// Compares lhs and rhs lexicographically by operator<, that is, compares the first elements 
	// and only if they are equivalent, compares the second elements

	template< class T1, class T2 >
	bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ 
		if (lhs.first<rhs.first)
			return true;
		else if (rhs.first<lhs.first)
			return false;
		else if (lhs.second<rhs.second)
			return true;
		return false;
	}

	template< class T1, class T2 >
	bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return rhs < lhs;
	}

	template< class T1, class T2 >
	bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif