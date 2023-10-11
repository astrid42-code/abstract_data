#include "includes/list.hpp"
#include <list>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void	main_list()
{
	std::cout << "########################### LIST ################################" << std::endl;
	list<int> test(15, 10);
	list<int> toto = test;
	
	std::cout << *toto.begin() << std::endl;

	// test_push_erase();
	// std::cout << std::endl;
	// test_popback();
	// std::cout << std::endl;
	// test_reserve();
	// std::cout << std::endl;
	// test_resize();
	// std::cout << std::endl;
	// test_swap();
	// std::cout << std::endl;
	// test_insert();
	// std::cout << std::endl;
	// test_assign();
	// std::cout << std::endl;
	// test_operator();
}

#endif