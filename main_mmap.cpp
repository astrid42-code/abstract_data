#include "includes/multimap.hpp"
#include "includes/rbt.hpp"
#include <map>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;


bool fncomp_mmap (char lhs, char rhs) 
{return lhs<rhs;}

struct classcomp_mmap
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

int main_mmap ()
{
 
    // initialize container
    multimap<int, int> mp;
	multimap<int, int>::iterator itr = mp.begin();
 
    // insert elements in random order
    mp.insert( 2, 30 );
    mp.insert( 1, 40 );
    mp.insert( 3, 60 );
    mp.insert( 2, 20 );
    mp.insert( 5, 50 );
 
    // prints the elements
    std::cout << "KEY\tELEMENT\n";
    for (; itr != mp.end(); ++itr) 
	{
        std::cout << itr->first << '\t' << itr->second << '\n';
    }
    return 0;
}