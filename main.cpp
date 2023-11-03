/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:46:30 by asgaulti          #+#    #+#             */
/*   Updated: 2023/01/18 10:46:35 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "includes/stack.hpp"
#include "includes/vector.hpp"
#include "includes/map.hpp"
#include "includes/set.hpp"

#include "main_stack.cpp"
#include "main_vector.cpp"
#include "main_map.cpp"
#include "main_set.cpp"
#include "main_deque.cpp"
#include "main_queue.cpp"
#include "main_mmap.cpp"
// #include "main_pqueue.cpp" // ne compile pas, a revoir
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <deque>

void	print_res(int i, std::string name)
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

int main(int ac, char *av[])
{
	(void)av;
	if (ac != 1)
		return (1);
	// main_queue();
	// main_list();
	// main_mmap();
	// main_pqueue();
	// main_deque();
	// main_stack();
	// main_vector();
	main_map();
	// main_set();
	return (0);
}
