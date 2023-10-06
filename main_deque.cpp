#include "includes/deque.hpp"
#include <deque>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void test_push_deque()
{
	std::cout << "		######## pushback/iterators ########" << std::endl;
	

	// std::deque<int> mydeque;
	// int myint;

	// std::cout << "Please enter some integers (enter 0 to end):\n";

	// do {
	// 	std::cin >> myint;
	// 	mydeque.push_back (myint);
	// } while (myint); // attention rajouter conditions : si myint pas un int genre avec !=isdigit() ?

	// std::cout << "mydeque stores " << (int) mydeque.size() << " numbers.\n";

	deque<int> mydeque2;
	for (int i=1; i<=5; i++) 
	{
		mydeque2.push_back(i);
		// std::cout << "mydeque2 contains:" << mydeque2[i] << std::endl;
		// le cout plante, checker les valeurs de mon deque avec un iterator, comme en dessous
	}
	std::cout << "at least mydeque2 contains:";
	deque<int>::iterator it = mydeque2.begin();
	while (it != mydeque2.end())
		std::cout << ' ' << *it++;
	std::cout << '\n';

}

void test_deque_operator()
{
	std::cout << "		######## operator = ########" << std::endl;
	deque<int> first (3);    // deque with 3 zero-initialized ints
	deque<int> second (5);   // deque with 5 zero-initialized ints

	second = first;
	first = deque<int>();

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
}


void	main_deque()
{
	std::cout << "########################### DEQUE ################################" << std::endl;
	// deque<int> test(15, 10);
	// deque<int> toto = test;
	
	// std::cout << *toto.begin() << std::endl;

	// constructors used in the same order as described above:
	deque<int> first;                                // empty deque of ints
	deque<int> second (4,100);                       // four ints with value 100
	deque<int> third (second.begin(),second.end());  // iterating through second
	deque<int> fourth (third);                       // a copy of third

	std::cout << " is first empty ? (0 false 1 : true) " << first.empty() << std::endl;
	std::cout << " is second empty ? (0 false 1 : true) " << second.empty() << std::endl;

	// the iterator constructor can be used to copy arrays:
	int myints[] = {16,2,77,29};
	deque<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );


	std::cout << "The contents of fifth are:";
	for (deque<int>::iterator it = fifth.begin(); it!=fifth.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	// test_deque_operator();
	// std::cout << std::endl;
	test_push_deque();
	std::cout << std::endl;
// 	test_push_erase();
// 	test_popback();
// 	std::cout << std::endl;
// 	test_reserve();
// 	std::cout << std::endl;
// 	test_resize();
// 	std::cout << std::endl;
// 	test_swap();
// 	std::cout << std::endl;
// 	test_insert();
// 	std::cout << std::endl;
// 	test_assign();
// 	std::cout << std::endl;
// 	test_operator();

}
