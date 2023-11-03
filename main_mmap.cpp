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
	std::cout << "is my mmap empty ? (0 : false / 1 : true) " << mymultimap.empty() << "\n";

	multimap<char,int> mymultimap2;

	mymultimap2.insert(make_pair('x',100));
	mymultimap2.insert(make_pair('y',200));
	mymultimap2.insert(make_pair('y',350));
	mymultimap2.insert(make_pair('z',500));

	std::cout << '\n';

	std::cout << "########## SIZE ##########\n";
	std::cout << "mymultimap2.size() is " << mymultimap2.size() << '\n';

	std::cout << '\n';

	std::cout << "########## SWAP ##########\n";
	multimap<char,int> foo,bar;

	foo.insert(make_pair('x',100));
	foo.insert(make_pair('y',200));

	bar.insert(make_pair('a',11));
	bar.insert(make_pair('b',22));
	bar.insert(make_pair('a',55));

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (multimap<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';

	std::cout << "bar contains:\n";
	for (multimap<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';
	
	std::cout << '\n';
	std::cout << "########## CLEAR ##########\n";

	multimap<char,int> mymultimap3;
	multimap<char,int>::iterator it;

	mymultimap3.insert(pair<char,int>('b',80));
	mymultimap3.insert(pair<char,int>('b',120));
	mymultimap3.insert(pair<char,int>('q',360));

	std::cout << "mymultimap3 contains:\n";
	for (it=mymultimap3.begin(); it!=mymultimap3.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';

	mymultimap3.clear();

	mymultimap3.insert(pair<char,int>('a',11));
	mymultimap3.insert(pair<char,int>('x',22));

	std::cout << "mymultimap3 contains:\n";
	for (it=mymultimap3.begin(); it != mymultimap3.end(); ++it)
		std::cout << (*it).first << " => " << (*it).second << '\n';

	std::cout << '\n';
	std::cout << "########## FIND / COUNT / BOUND ##########\n";

	multimap<char,int> mymm;

	mymm.insert (make_pair('x',10));
	mymm.insert (make_pair('y',20));
	mymm.insert (make_pair('z',30));
	mymm.insert (make_pair('z',40));

	multimap<char,int>::iterator it2 = mymm.find('x');
	mymm.erase (it2);
	// mymm.get_rbt().print_prefix(mymm.get_rbt().getRoot(), 0);
	// mymm.erase (mymm.find('z'));

	// // print content:
	// std::cout << "elements in mymm:" << '\n';
	// std::cout << "y => " << mymm.find('y')->second << '\n';
	// std::cout << "z => " << mymm.find('z')->second << '\n';

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
	mymultimap.insert (it, pair<char,int>('d',400));
	mymultimap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting
	// mymultimap.get_rbt().print_prefix(mymultimap.get_rbt().getRoot(), 0);

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

	simple_tests();

	return 0;
}

// A faire : testeur pour differentes fcts 