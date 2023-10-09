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

// remplacer queue<int> par un template pour accepter autre chose que des 

void    test_queue_empty(queue<int> mq)
{
	std::cout << "########## EMPTY ##########\n";
	// queue<int> myqueue;
	int sum (0);

	// for (int i=1;i<=10;i++) myqueue.push(i);

	while (!mq.empty())
	{
		sum += mq.front();
		mq.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void	test_queue_size(queue<int> mq)
{
	std::cout << "########## SIZE ##########\n";

	// queue<int> myints;
	std::cout << "0. size: " << mq.size() << '\n';

	for (int i=0; i<5; i++) mq.push(i);
	std::cout << "1. size: " << mq.size() << '\n';

	mq.pop();
	std::cout << "2. size: " << mq.size() << '\n';
}

void	test_queue_front(queue<int> mq)
{
	std::cout << "########## FRONT ##########\n";

	// queue<int> myqueue;

	mq.push(10);
	mq.push(20);

	mq.front() -= 5;

	std::cout << "mq.front() is now " << mq.front() << '\n';
}

void	test_queue_push(queue<int> mq)
{
	std::cout << "########## PUSH ##########\n";

	// queue<int> myqueue;

	// for (int i=0; i<5; ++i) myqueue.push(i);

	std::cout << "Popping out elements...";
	while (!mq.empty())
	{
		std::cout << ' ' << mq.front();
		mq.pop();
	}
	std::cout << '\n';

	// int myint;

	// std::cout << "Please enter some integers (enter 0 to end):\n";

	// do {
	// 	std::cin >> myint;
	// 	mq.push (myint);
	// } while (myint);

	// std::cout << "mq contains: ";
	// while (!mq.empty())
	// {
	// 	std::cout << ' ' << mq.front();
	// 	mq.pop();
	// }
	// std::cout << '\n';

}

void	test_queue_pop(queue<int> mq)
{
	std::cout << "########## POP ##########\n";
	
	// queue<int> myqueue;

	// for (int i=0; i<5; ++i) myqueue.push(i);

	std::cout << "Popping out elements...";
	while (!mq.empty())
	{
		std::cout << ' ' << mq.front();
		mq.pop();
	}
	std::cout << '\n';

}

void	main_queue()
{

	std::cout << "########################### QUEUE ################################" << std::endl;

	queue<int> myqueue;

	for (int i=0; i<5; ++i) myqueue.push(i);
	test_queue_empty(myqueue);
	std::cout << std::endl;
	test_queue_size(myqueue);
	std::cout << std::endl;
	test_queue_front(myqueue);
	std::cout << std::endl;
	test_queue_push(myqueue);
	std::cout << std::endl;
	test_queue_pop(myqueue);
	std::cout << std::endl;
}