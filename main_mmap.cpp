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
//   multimap<char,int> first;

//   first.insert(ft::pair<char,int>('a',10));
//   first.insert(ft::pair<char,int>('b',15));
//   first.insert(ft::pair<char,int>('b',20));
//   first.insert(ft::pair<char,int>('c',25));

//   multimap<char,int> second (first.begin(),first.end());

//   multimap<char,int> third (second);

//   multimap<char,int,classcomp> fourth;                 // class as Compare

//   bool(*fn_pt)(char,char) = fncomp;
//   multimap<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as comp

//     // initialize container
//     multimap<int, int> mp;
 
//     // insert elements in random order
//     mp.insert(ft::pair<int,int>( 2, 30 ));
//     mp.insert(ft::pair<int,int>( 1, 40 ));
//     mp.insert(ft::pair<int,int>( 3, 60 ));
//     mp.insert(ft::pair<int,int>( 2, 20 ));
//     mp.insert(ft::pair<int,int>( 5, 50 ));
 
// 	multimap<int, int>::iterator itr = mp.begin();
//     // prints the elements
//     std::cout << "KEY\tELEMENT\n";
//     for (; itr != mp.end(); ++itr) 
// 	{
//         std::cout << itr->first << '\t' << itr->second << '\n';
//     }
//     return 0;

	multimap<char,int> mymultimap;
	multimap<char,int>::iterator it;

	// first insert function version (single parameter):
	mymultimap.insert ( pair<char,int>('a',100) );
	mymultimap.insert ( pair<char,int>('z',150) );
	it=mymultimap.insert ( pair<char,int>('b',75) );

	// second insert function version (with hint position):
	mymultimap.insert (it, pair<char,int>('c',300));  // max efficiency inserting 
	mymultimap.insert (it, pair<char,int>('z',400));  // no max efficiency inserting


	mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);


	// showing contents:
	std::cout << "mymultimap contains:\n";
	for (it=mymultimap.begin(); it!=mymultimap.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';

	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);


	// third insert function version (range insertion):
	// multimap<char,int> anothermultimap;
	// anothermultimap.insert(mymultimap.begin(),mymultimap.find('c'));

	// std::cout << "anothermultimap contains:\n";
	// for (it=anothermultimap.begin(); it!=anothermultimap.end(); ++it)
	// 	std::cout << (*it).first << " => " << (*it).second << '\n';
	// // anothermultimap.get_rbt().print_prefix(anothermultimap.get_rbt().getRoot(), 0);



	return 0;
}

// Pbs a regler :
// insert du c, 300 ne se fait pas, pk? si on enleve le c, 30, plus de souci (donc pb avec le max efficiency inserting)
// leak du a un pb de clear du rbt?
// insert 3 a regler pour compiler > ok mais difference au resultat dans l'ordre ou sont donnes les deux z 
// > imprimer le rbt pour voir > pb commentappeler la methode?(getter le rbt (mais comment?) puis faire print_prefix(???, 0)