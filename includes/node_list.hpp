#ifndef NODE_LIST_HPP
#define NODE_LIST_HPP

#include <iostream>


namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class list

	class node_list
	{
		public:
			int 		key;        // Champ de données
			node_list*	next;     // pointeur vers le nœud suivant

			// Fonction utilitaire pour renvoyer un nouveau nœud de liste chaînée à partir du heap
			node_list* newNode(int key)
			{
				// alloue le nouveau nœud dans un heap en utilisant le nouvel opérateur et définit ses données
				node_list* node = new node_list;
				node->key = key;
			
				// définit le pointeur `.next` du nouveau nœud pour qu'il pointe sur null
				node->next = nullptr;
			
				return node;
			}
	};
	// {
	// 	public:
	// 		typedef T			value_type;
	// 		typedef node		*node_ptr;
	// 		typedef const node	*const_node_ptr;
	// 		typedef node		&reference;
	// 		typedef const node	&const_ref;

	// 		node_ptr			left_child;
	// 		node_ptr			right_child;
	// 		node_ptr			parent;
	// 		int					color;
	// 		value_type			pair;

	// 		// constructors
	// 		node() {
	// 			left_child = NULL;
	// 			right_child = NULL;
	// 			parent = NULL;
	// 			color = RED;
	// 		}

	// 		node(const value_type val, node_ptr newparent = NULL, 
	// 				node_ptr leftChild = NULL, node_ptr rightChild = NULL)
	// 			: left_child(leftChild), right_child(rightChild), parent(newparent), color(RED), pair(val)
	// 		{ }

	// 		// copy constructor 
	// 		node(const_ref node_cp)
	// 			: left_child(node_cp.left_child), right_child(node_cp.right_child), parent(node_cp.parent),
	// 			color(node_cp.color), pair(node_cp.pair) {}

	// 		// destructor 
	// 		~node() {}

	// 		reference	operator=(const_ref node_op) {
	// 			left_child = node_op.left_child;
	// 			right_child = node_op.right_child;
	// 			parent = node_op.parent;
	// 			color = node_op.color;
	// 			return (*this);
	// 		}

	// };
}


#endif