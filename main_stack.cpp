#include <iostream>
#include <string>
#include <deque>
#include "includes/stack.hpp"
#include <stack>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void	print_res_stack(int i, std::string name)
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

void    test_empty()
{
	//########################### EMPTY ################################
	print_res_stack(0, "empty ");
	stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void	test_size()
{
	//########################### SIZE ################################
	print_res_stack(0, "size ");

	stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

void	test_top()
{
	//########################### TOP ################################
	print_res_stack(0, "top ");

	stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void	test_push()
{
	//########################### PUSH ################################
	print_res_stack(0, "push ");

	stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';
}

void	test_pop()
{
	//########################### POP ################################
	print_res_stack(0, "pop ");
	stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';

}

void	main_stack()
{

	std::cout << "########################### STACK ################################" << std::endl;

	test_empty();
	std::cout << std::endl;
	test_size();
	std::cout << std::endl;
	test_top();
	std::cout << std::endl;
	test_push();
	std::cout << std::endl;
	test_pop();
	std::cout << std::endl;
}