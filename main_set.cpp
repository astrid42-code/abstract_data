#include <iostream>
#include <string>
#include "includes/set.hpp"
#include "includes/rbt_it_set.hpp"
#include <set>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void	print_res_set(int i, std::string name)
{
	switch(i)
	{
		case 1 : std::cout << "Is my map empty? (0 false, 1 true) : ";
		break;
		case 2 : std::cout << " size = ";
		break;
		case 100 : std::cout << " So nice to have you here! Let's survive to this together..." << std::endl;
		default : std::cout << "###### " << " " << name << "######" << std::endl;
	}
}

void	test_op()
{
	print_res_set(0, " operator= ");
	int myints[]={ 12,82,37,64,15 };
	set<int> first (myints,myints+5);   // set with 5 ints
	set<int> second;                    // empty set

	second = first;                          // now second contains the 5 ints
	first = set<int>();                 // and first is empty

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
}

void	test_modifiers()
{
	//########################### CLEAR/INSERT/ERASE ################################
	print_res_set(0, "insert ");

	set<int> myset;
	set<int>::iterator it;
	pair<set<int>::iterator,bool> ret;

	// set some initial values:
	for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

	ret = myset.insert(20);               // no new element inserted

	if (ret.second==false) it=ret.first;  // "it" now points to element 20

	myset.insert (it,25);                 // max efficiency inserting
	myset.insert (it,24);                 // max efficiency inserting
	myset.insert (it,26);                 // no max efficiency inserting

	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset.insert (myints,myints+3);

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myset.clear();

	print_res_set(0, "insert/erase ");
	set<int>::iterator it2;

	// insert some values:
	for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

	it2 = myset.begin();
	++it2; // "it2" points now to 20

	myset.erase (it2);

	myset.erase (40);

	it2 = myset.find (60);
	myset.erase (it2, myset.end());

	std::cout << "myset contains:";
	for (it2=myset.begin(); it2!=myset.end(); ++it2)
		std::cout << ' ' << *it2;
	std::cout << '\n';

	std::cout << std::endl;

	//########################### SWAP ################################
	print_res_set(0, "swap ");

	int myints2[]={12,75,10,32,20,25};
	set<int> first (myints2,myints2+3);     // 10,12,75
	set<int> second (myints2+3,myints2+6);  // 20,25,32

	first.swap(second);

	std::cout << "after swap first contains:";
	for (set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << " and second contains:";
	for (set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

}

void	test_operations()
{
	//########################### FIND ################################
	print_res_set(0, "find ");

	set<int> myset;
	set<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

	it=myset.find(20);
	myset.erase (it);
	myset.erase (myset.find(40));

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myset.clear();
	std::cout << "after clear : " ; 
	print_res_set(1, "  ");
	std::cout << myset.empty() << std::endl;

	std::cout << std::endl;
	//########################### COUNT ################################
	print_res_set(0, "count ");

	// set some initial values:
	for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

	for (int i=0; i<10; ++i)
	{
		std::cout << i;
		if (myset.count(i)!=0)
		std::cout << " is an element of myset.\n";
		else
		std::cout << " is not an element of myset.\n";
	}

	myset.clear();

	std::cout << std::endl;

	//########################### UPPER/LOWER_BOUND/EQUAL_RANGE ################################
	print_res_set(0, "upper/lower_bound/equal_range ");

	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

	pair<set<int>::const_iterator,set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';

	std::cout << std::endl;
	
}

void	test_capacity()
{
	//########################### SIZE ################################
	print_res_set(0, "size ");

	set<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; ++i) myints.insert(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.erase(5);
	std::cout << "3. size: " << myints.size() << '\n';

	std::cout << std::endl;

	//########################### MAX_SIZE ################################
	print_res_set(0, "max_size ");

	int i;
	set<int> myset;

	if (myset.max_size()>1000)
	{
		for (i=0; i<1000; i++) myset.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	}
	else std::cout << "The set could not hold 1000 elements.\n";
}

void	test_observers()
{
	//########################### KEY_COMP ################################
	print_res_set(0, "key_comp ");

	set<int> myset;
	int highest;

	set<int>::key_compare mycomp = myset.key_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	highest=*myset.rbegin();
	set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';

	std::cout << std::endl;

	//########################### VALUE_COMP ################################
	print_res_set(0, "value_comp ");

	set<int> myvalueset;

	set<int>::value_compare myvaluecomp = myvalueset.value_comp();

	for (int i=0; i<=5; i++) myvalueset.insert(i);

	std::cout << "myvalueset contains:";

	int highestvalue=*myvalueset.rbegin();
	set<int>::iterator it2=myvalueset.begin();
	do {
		std::cout << ' ' << *it2;
	} while ( myvaluecomp(*(++it2),highestvalue) );

	std::cout << '\n';

}

void	test_it()
{
	//########################### BEGIN/END ################################
	print_res_set(0, "begin/end ");

	int myints[] = {75,23,65,42,13};
	set<int> myset (myints,myints+5);

	std::cout << "myset contains:";
	for (set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	std::cout << std::endl;

	//########################### RBEGIN/REND ################################
	print_res_set(0, "rbegin/rend ");

	int myints2[] = {21,64,17,78,49};
	set<int> myrevset (myints2,myints2+5);

	set<int>::reverse_iterator rit;

	std::cout << "myrevset contains:";
	for (rit=myrevset.rbegin(); rit != myrevset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}

bool fncomp (int lhs, int rhs)
{
	return lhs<rhs;
}

struct classcomp
{
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

void	main_set ()
{
	std::cout << "########################### SET ################################" << std::endl;
	print_res_set(0, "Set constructors ");
	set<int> first;                           // empty set of ints

	std::cout << "Default constructor : ok\nsize = " << first.size() << "\n";
	print_res_set(1, "  ");
	std::cout << first.empty() << std::endl;

	int myints[]= {10,20,30,40,50};
	set<int> second (myints,myints+5);        // range

	std::cout << "Range constructor : ok" << std::endl;

	set<int> third (second);                  // a copy of second
	std::cout << "Copy constructor : ok" << std::endl;

	set<int> fourth (second.begin(), second.end());  // iterator ctor.
	std::cout << "Iterator constructor : ok" << std::endl;


	set<int,classcomp> fifth;                 // class as Compare

	bool(*fn_pt)(int,int) = fncomp;
	set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

	std::cout << "Compare : ok" << std::endl;

	test_op();
	std::cout << std::endl;

	test_modifiers();
	std::cout << std::endl;

	test_operations();
	std::cout << std::endl;

	test_capacity();
	std::cout << std::endl;

	test_observers();
	std::cout << std::endl;

	test_it();
	std::cout<< std::endl;
}