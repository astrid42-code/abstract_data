#include "includes/deque.hpp"
#include <deque>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

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

	test_deque_operator();
	std::cout << std::endl;
	
// 	test_push_erase();
// 	std::cout << std::endl;
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
