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

void simple_tests()
{
	std::cout << "########## EMPTY ##########\n";

	multimap<char,int> mymultimap;

	mymultimap.insert (pair<char,int>('b',101));
// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
	mymultimap.insert (pair<char,int>('b',202));
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
	mymultimap.insert (pair<char,int>('q',505));
// std::cout << " begin = " << mymultimap.get_rbt().getBegin(mymultimap.get_rbt().getRoot())->pair.first << " " << mymultimap.get_rbt().getBegin(mymultimap.get_rbt().getRoot())->pair.second << "\n";
// std::cout << " root = " << mymultimap.get_rbt().getRoot()->pair.first << " " << mymultimap.get_rbt().getRoot()->pair.second << "\n";
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);


// pb dans insertion/fixup (b 202 devrait devenir la root et non un left_child )

	while (!mymultimap.empty())
	{
		std::cout << mymultimap.begin()->first << " => ";
		std::cout << mymultimap.begin()->second << '\n';
		mymultimap.erase(mymultimap.begin()); 
	// pb dans erase? verifier le rbt dans la boucle pour cmrendre pk il ecrit 202 2 fois

	}
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
}


int main_mmap ()
{
 	multimap<char,int> mymultimap;
	multimap<char,int>::iterator it;

	// first insert function version (single parameter):
	mymultimap.insert ( pair<char,int>('a',100) );
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
	mymultimap.insert ( pair<char,int>('z',150) );
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
	it=mymultimap.insert ( pair<char,int>('b',75) );
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);

	// second insert function version (with hint position):
	mymultimap.insert (it, pair<char,int>('c',300));  // max efficiency inserting 
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
	
	

	mymultimap.insert (it, pair<char,int>('z',500));
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);
	// mymultimap.insert (it, pair<char,int>('d',400));
	mymultimap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

	// showing contents:
	std::cout << "mymultimap contains:\n";
	for (it=mymultimap.begin(); it!=mymultimap.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';



	// third insert function version (range insertion):
	multimap<char,int> anothermultimap;
	// anothermultimap.insert(mymultimap.begin(),mymultimap.find('c'));
	// result ft/std != mais ok car cas undefined : cf point 1.2 de find (joachim discord le 31/10))
	anothermultimap.insert(mymultimap.begin(),mymultimap.lower_bound('c'));

	std::cout << "anothermultimap contains:\n";
	for (it=anothermultimap.begin(); it!=anothermultimap.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';
	// anothermultimap.get_rbt().print_prefix(anothermultimap.get_rbt().getRoot(), 0);

	// simple_tests();

	return 0;
}

// A faire : testeur pour differentes fcts 