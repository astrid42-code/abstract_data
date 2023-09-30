
#include "includes/vector.hpp"
#include <vector>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void	print_res_vector(int i, std::string name)
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

void	test_push_erase()
{
	//########################### PUSH/ERASE ################################
	print_res_vector(0, "push/erase ");
	vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++)
		myvector.push_back(i);

	// erase the 6th element
	myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin(),myvector.begin()+3);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << std::endl;

	std::cout << std::endl;
		
}

void  test_popback()
{
	//########################### POPBACK ################################
	print_res_vector(0, "popback ");
	vector<int> myvector;
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << std::endl;
		
	vector<size_t> numbers;
	
	numbers.push_back(5);
	numbers.push_back(3);
	numbers.push_back(4);
	
	std::cout << '[';
	for (size_t i = 0; i < numbers.size(); i++){
		std::cout << numbers[i] << ' ';
	}
	std::cout << "]\n";

	numbers.pop_back();

	std::cout << '[';
	for (size_t i = 0; i < numbers.size(); i++){
		std::cout << numbers[i] << ' ';
	}
	std::cout << "]\n";

	std::cout << std::endl;
}

void test_reserve(){
	//########################### RESERVE ################################
	print_res_vector(0, "reserve ");

	vector<int>::size_type sz;

	vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i)
	{
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << std::endl;
		}
	}
	std::cout << std::endl;
	vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << std::endl;
		}
	}

	std::cout << std::endl;
}


void test_resize(){
	//########################### RESIZE ################################
	print_res_vector(0, "resize ");

	vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++)
		myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << std::endl;

	std::cout << std::endl;
	
}

void  test_swap()
{
	//########################### SWAP ################################
	print_res_vector(0, "swap ");

	vector<int> v1(5, 3);
	vector<int> v2(3, 5);
		
	std::cout << "\n AVANT \n _begin : ";
	for (size_t i=0; i<v1.size(); i++)
		std::cout << v1[i] << (i != v1.size() - 1 ? ", " : "");
	std::cout << "\n_size: " << v1.size() << std::endl;
	std::cout << "_capacity: " << v1.capacity() << std::endl;
	if (!v1.empty()) {
		std::cout << "front: " << v1.front() << std::endl;
		std::cout << "back: " << v1.back() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\n_begin: ";
	for (size_t i=0; i<v2.size(); i++)
		std::cout << v2[i] << (i != v2.size() - 1 ? ", " : "");
	std::cout << "\n_size: " << v2.size() << std::endl;
	std::cout << "_capacity: " << v2.capacity() << std::endl;
	if (!v2.empty()) {
		std::cout << "front: " << v2.front() << std::endl;
		std::cout << "back: " << v2.back() << std::endl;
	}
	std::cout << std::endl;

	v1.swap(v2);

	std::cout << "\n APRES \n _begin : ";
	for (size_t i=0; i<v1.size(); i++)
		std::cout << v1[i] << (i != v1.size() - 1 ? ", " : "");
	std::cout << "\n_size: " << v1.size() << std::endl;
	std::cout << "_capacity: " << v1.capacity() << std::endl;
	if (!v1.empty()) {
		std::cout << "front: " << v1.front() << std::endl;
		std::cout << "back: " << v1.back() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\n_begin: ";
	for (size_t i=0; i<v2.size(); i++)
		std::cout << v2[i] << (i != v2.size() - 1 ? ", " : "");
	std::cout << "\n_size: " << v2.size() << std::endl;
	std::cout << "_capacity: " << v2.capacity() << std::endl;
	if (!v2.empty()) {
		std::cout << "front: " << v2.front() << std::endl;
		std::cout << "back: " << v2.back() << std::endl;
	}
	std::cout << std::endl;
}


void test_insert()
{
	//########################### INSERT ################################
	print_res_vector(0, "insert ");

	vector<int> myvector (3,100);
	vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it + 2,2,300);
	std::cout << "1 myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	vector<int> anothervector (2,400);
	myvector.insert (it+1,anothervector.begin(),anothervector.end());

	std::cout << "2 myvector2 contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin() + 3, myarray, myarray+3);

	std::cout << "3 myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;

}

// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
void test_assign()
{
	//########################### ASSIGN ################################
	print_res_vector(0, "assign ");

	vector<int> first;
	vector<int> second;
	vector<int> third;

	first.assign (7,100);            // 7 ints with a value of 100

	vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	for (size_t i = 0; i < first.size(); i++){
		std::cout << "first" << i << " " << first[i] << std::endl;
	}
	std::cout << "Size of first: " << int (first.size()) << std::endl;
	for (size_t i = 0; i < second.size(); i++){
		std::cout << second[i] << std::endl;
	}
	std::cout << "Size of second: " << int (second.size()) << std::endl;
	for (size_t i = 0; i < third.size(); i++){
		std::cout << third[i] << std::endl;
	}
	std::cout << "Size of third: " << int (third.size()) << std::endl;
	std::cout << std::endl;

}

void test_operator()
{
	//########################### OPERATORS ################################
	print_res_vector(0, "operators ");
	vector<std::string> v1(10, "salut");
	vector<std::string> v2(10, "salut");

	v2[4] = "coucou";

	std::cout << (v1 == v2) << ", ";
	std::cout << (v1 != v2) << ", ";
	std::cout << (v1 < v2) << ", ";
	std::cout << (v1 > v2) << ", ";
	std::cout << (v1 <= v2) << ", ";
	std::cout << (v1 >= v2) << std::endl;

	std::cout << (v1 == v1) << ", ";
	std::cout << (v1 != v1) << ", ";
	std::cout << (v1 < v1) << ", ";
	std::cout << (v1 > v1) << ", ";
	std::cout << (v1 <= v1) << ", ";
	std::cout << (v1 >= v1) << std::endl;

	std::cout << std::endl;
}

void	main_vector()
{
	std::cout << "########################### VECTOR ################################" << std::endl;
	vector<int> test(15, 10);
	vector<int> toto = test;
	
	std::cout << *toto.begin() << std::endl;

	test_push_erase();
	std::cout << std::endl;
	test_popback();
	std::cout << std::endl;
	test_reserve();
	std::cout << std::endl;
	test_resize();
	std::cout << std::endl;
	test_swap();
	std::cout << std::endl;
	test_insert();
	std::cout << std::endl;
	test_assign();
	std::cout << std::endl;
	test_operator();
}
