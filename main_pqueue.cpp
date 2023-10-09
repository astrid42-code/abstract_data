#include <iostream>
#include <string>
#include <deque>
#include "includes/queue.hpp"
#include "includes/priority_queue.hpp"
#include <queue>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;


void    test_pqueue_empty(priority_queue<int> mpq)
{
	std::cout << "########## EMPTY ##########\n";
	// queue<int> myqueue;
	int sum (0);

	// for (int i=1;i<=10;i++) myqueue.push(i);

	while (!mpq.empty())
	{
		sum += mpq.top();
		mpq.pop();
	}

	std::cout << "total: " << sum << '\n';
}

void	test_pqueue_size(priority_queue<int> mpq)
{
	std::cout << "########## SIZE ##########\n";

	// queue<int> myints;
	std::cout << "0. size: " << mpq.size() << '\n';

	for (int i=0; i<5; i++) mpq.push(i);
	std::cout << "1. size: " << mpq.size() << '\n';

	mpq.pop();
	std::cout << "2. size: " << mpq.size() << '\n';
}

void	test_pqueue_front(priority_queue<int> mpq)
{
	std::cout << "########## FRONT ##########\n";

	// queue<int> myqueue;

	mpq.push(10);
	mpq.push(20);

	mpq.front() -= 5;

	std::cout << "mpq.front() is now " << mpq.front() << '\n';
}

void	test_pqueue_push(priority_queue<int> mpq)
{
	std::cout << "########## PUSH ##########\n";

	// queue<int> myqueue;

	// for (int i=0; i<5; ++i) myqueue.push(i);

	std::cout << "Popping out elements...";
	while (!mpq.empty())
	{
		std::cout << ' ' << mpq.front();
		mpq.pop();
	}
	std::cout << '\n';

	// int myint;

	// std::cout << "Please enter some integers (enter 0 to end):\n";

	// do {
	// 	std::cin >> myint;
	// 	mpq.push (myint);
	// } while (myint);

	// std::cout << "mpq contains: ";
	// while (!mpq.empty())
	// {
	// 	std::cout << ' ' << mpq.front();
	// 	mpq.pop();
	// }
	// std::cout << '\n';

}

void	test_pqueue_pop(priority_queue<int> mpq)
{
	std::cout << "########## POP ##########\n";
	
	// queue<int> myqueue;

	// for (int i=0; i<5; ++i) myqueue.push(i);

	std::cout << "Popping out elements...";
	while (!mpq.empty())
	{
		std::cout << ' ' << mpq.front();
		mpq.pop();
	}
	std::cout << '\n';

}

void	main_pqueue()
{

	std::cout << "########################### PRIORITY_QUEUE ################################" << std::endl;

	priority_queue<int> mypqueue;

	for (int i=0; i<5; ++i) mypqueue.push(i);
	test_pqueue_empty(mypqueue);
	std::cout << std::endl;
	test_pqueue_size(mypqueue);
	std::cout << std::endl;
	test_pqueue_front(mypqueue);
	std::cout << std::endl;
	test_pqueue_push(mypqueue);
	std::cout << std::endl;
	test_pqueue_pop(mypqueue);
	std::cout << std::endl;
}