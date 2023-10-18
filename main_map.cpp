/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:44:04 by asgaulti          #+#    #+#             */
/*   Updated: 2022/11/16 20:16:30 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/map.hpp"
#include "includes/rbt.hpp"
#include <map>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void	print_res_map(int i, std::string name)
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

// TEST OPERATIONS
void	test_op_map()
{
	//########################### FIND ################################
	print_res_map(0, "find ");
	map<char,int> mymap;
	map<char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase (it);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';

	//########################### COUNT ################################
	std::cout << '\n';
	print_res_map(0, "count ");
	map<char,int> mymap2;
	char c;

	mymap2 ['a']=101;
	mymap2 ['c']=202;
	mymap2 ['f']=303;

	for (map<char,int>::iterator it=mymap2.begin(); it!=mymap2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap2.count(c)>0)
		std::cout << " is an element of mymap2.\n";
		else 
		std::cout << " is not an element of mymap2.\n";
	}

	//########################### LOWER_BOUND/UPPER_BOUND ################################
	std::cout << '\n';
	print_res_map(0, "upper/lower_bound ");
	map<char,int> mymap3;
	map<char,int>::iterator itlow,itup;

	mymap3['a']=20;
	mymap3['b']=40;
	mymap3['c']=60;
	mymap3['d']=80;
	mymap3['e']=100;

	itlow=mymap3.lower_bound ('b');  // itlow points to b
	itup=mymap3.upper_bound ('d');   // itup points to e (not d!)

	mymap3.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (map<char,int>::iterator it=mymap3.begin(); it!=mymap3.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	//########################### EQUAL_RANGE ################################
	std::cout << '\n';
	print_res_map(0, "equal_range ");

	map<char,int> mymap4;

	mymap4['a']=10;
	mymap4['b']=20;
	mymap4['c']=30;

	pair<map<char,int>::iterator,map<char,int>::iterator> ret;
	ret = mymap4.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

}

// TEST OBSERVERS
void	test_observers_map()
{
	//########################### KEY_COMP ################################
	print_res_map(0, "key_comp ");
	map<char,int> mymap;

	map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first;     // key value of last element

	map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << '\n';

	//########################### VALUE_COMP ################################
	print_res_map(0, "value_comp ");

	map<char,int> mymap2;

	mymap2['x']=1001;
	mymap2['y']=2002;
	mymap2['z']=3003;

	std::cout << "mymap2 contains:\n";

	pair<char,int> highest2 = *mymap2.rbegin();          // last element

	map<char,int>::iterator it2 = mymap2.begin();
	do {
		std::cout << it2->first << " => " << it2->second << '\n';
	} while ( mymap2.value_comp()(*it2++, highest2) );


}

// TEST ELEMENT ACCESS

void	test_elementaccess()
{
	//########################### [ ] ################################
	print_res_map(0, "[ ] ");
	map<char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']= mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n'; // key d has no value

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";


}

// TEST modifiers (swap, )
void	test_modifiers_map()
{
	//########################### SWAP ################################

	print_res_map(0, "swap ");
	map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	std::cout <<  " before swap foo countains " << std::endl;
	for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout <<  " before swap bar countains "<< std::endl;
	for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	
	foo.swap(bar);

	std::cout <<  " after swap foo countains "<< std::endl;
	for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout <<  " after swap bar countains "<< std::endl;
	for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	//########################### CLEAR/INSERT/ERASE ################################

	std::cout << std::endl;
	print_res_map(0, "clear/insert/erase ");

	foo.clear();

	print_res_map(1, "empty/size");
	std::cout << foo.empty(); // comment envoyer mymap a la fct print?
	print_res_map(2, "empty/size");
	std::cout << foo.size() << std::endl;

	std::cout << std::endl;
	
	bar.clear();

	map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( pair<char,int>('a',100) );
	mymap.insert ( pair<char,int>('z',200) );

	pair<map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains before erase:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	std::cout << "mymap contains after erase:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

// TEST capacity (empty, size, maxsize)
void	test_capacity_map(void)
{
	//########################### EMPTY/SIZE ################################

	print_res_map(0, "empty/size ");

	map<char,int> mymap;

	print_res_map(1, "empty/size");
	std::cout << mymap.empty(); // comment envoyer mymap a la fct print?
	print_res_map(2, "empty/size");
	std::cout << mymap.size() << std::endl;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		print_res_map(1, "empty/size");
		std::cout << mymap.empty();
		print_res_map(2, "empty/size");
		std::cout << mymap.size() << std::endl;
		mymap.erase(mymap.begin());
	}
	print_res_map(1, "empty/size");
	std::cout << mymap.empty();
	print_res_map(2, "empty/size");
	std::cout << mymap.size() << std::endl;

	std::cout << std::endl;
	print_res_map(0, "empty/size ");
	
	map<char,int> mymap2;

	print_res_map(1, "empty/size");
	std::cout << mymap2.empty();
	print_res_map(2, "empty/size");
	std::cout << mymap2.size() << std::endl;

	mymap2['a']=10;
	mymap2['b']=20;
	mymap2['c']=30;

	while (!mymap2.empty())
	{
		std::cout << mymap2.begin()->first << " => " << mymap2.begin()->second << '\n';
		print_res_map(1, "empty");
		std::cout << mymap2.empty();
		print_res_map(2, "empty/size");
		std::cout << mymap2.size() << std::endl;
		mymap2.erase(mymap2.begin());
	}
	print_res_map(1, "empty");
	std::cout << mymap2.empty();
	print_res_map(2, "empty/size");
	std::cout << mymap2.size() << std::endl;

	std::cout << std::endl;
	//########################### MAX_SIZE ################################

	print_res_map(0, "max_size ");
	int i;
	map<int,int> mymap3;

	if (mymap3.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap3[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";

	std::cout << std::endl;

}


bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp_map
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

void	main_map()
{
	std::cout << "########################### MAP ################################" << std::endl;
	print_res_map (100, "");
	print_res_map(0, "Constructors");

	map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	std::cout << "Default constructor : OK " << std::endl;

	map<char,int> second (first.begin(),first.end());
	std::cout << "Range constructor : OK " << std::endl; 

	std::cout << "Copy constructor : OK " << std::endl; 
	map<char,int> third (second);

	map<char,int,classcomp_map> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	third = second;
	std::cout << "Overload operator = : OK" << std::endl;
	std::cout << std::endl;
	

	// test_capacity_map();
	// std::cout << std::endl;

	// test_modifiers_map();
	// std::cout << std::endl;

	// test_elementaccess();
	// std::cout << std::endl;

	// test_observers_map();
	// std::cout << std::endl;

	// test_op_map();
	// std::cout << std::endl;

	// fourth.~map();
	// std::cout << std::endl;
}
