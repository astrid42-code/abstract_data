#include <iostream>
#include <string>
#include <deque>
#include "includes/queue.hpp"
#include <queue>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

void    test_queue_empty()
{
	std::cout << "########## EMPTY ##########\n";
	queue<int> myqueue;
	int sum (0);

	for (int i=1;i<=10;i++) myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void	test_queue_size()
{
	std::cout << "########## SIZE ##########\n";

	queue<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';
}

void	test_queue_front()
{
	std::cout << "########## FRONT ##########\n";

	queue<int> myqueue;

	myqueue.push(10);
	myqueue.push(20);

	myqueue.front() -= 5;

	std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
}

void	test_queue_push()
{
	std::cout << "########## PUSH ##########\n";

	queue<int> myqueue;

	for (int i=0; i<5; ++i) myqueue.push(i);

	std::cout << "Popping out elements...";
	while (!myqueue.empty())
	{
		std::cout << ' ' << myqueue.front();
		myqueue.pop();
	}
	std::cout << '\n';
}

void	test_queue_pop()
{
	std::cout << "########## POP ##########\n";
	
	queue<int> myqueue;

	for (int i=0; i<5; ++i) myqueue.push(i);

	std::cout << "Popping out elements...";
	while (!myqueue.empty())
	{
		std::cout << ' ' << myqueue.front();
		myqueue.pop();
	}
	std::cout << '\n';

}

void	main_queue()
{

	std::cout << "########################### QUEUE ################################" << std::endl;

	test_queue_empty();
	std::cout << std::endl;
	test_queue_size();
	std::cout << std::endl;
	test_queue_front();
	std::cout << std::endl;
	test_queue_push();
	std::cout << std::endl;
	test_queue_pop();
	std::cout << std::endl;
}