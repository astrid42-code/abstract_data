#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include "node.hpp"
#include "make_pair.hpp"
#include "bi_directional_it.hpp"
#include "rbt_it.hpp"

#define BLACK 	0
#define RED 	1

namespace ft
{

	enum status
	{
		UNUIQUE = true,
		NOT_UNIQUE = false
	};

	template < class Type, class Cmp, class node = node<Type>, class AllocNode = std::allocator<node> >
	class rbt
	{
		public:
			typedef Type    																value_type;
			typedef typename value_type::first_type											key_type;
			typedef typename value_type::second_type										value;
			typedef Cmp 																	key_cmp;
			typedef AllocNode																alloc_node;
			typedef typename alloc_node::size_type											size_type;
			typedef typename node::node_ptr													node_ptr;
			typedef typename node::const_node_ptr											const_node_ptr;
			typedef typename node::reference												node_ref;
			typedef typename node::const_ref												const_node_ref;
			typedef typename ft::rbt_it<node, key_cmp>										iterator;
			typedef typename ft::rbt_const_it<node, key_cmp>								const_iterator;

		private:

			node_ptr	_root;
			node_ptr	_nil;
			key_cmp		_cmp;
			AllocNode	_alloc_rbt;
			size_t		_size;
			// status		unique_tree;

			// protected:

			
		public:
			// // print rbt fct 
			void    print_prefix( node_ptr cur, int level ) const
			{
					std::cout << std::string(2 * level, ' ');
					if (!cur)
							std::cout << "NULL (B)" << std::endl;
					else
					{
							std::cout << cur->pair.first << "(" << cur->pair.second;
							if (cur->color == RED)
									std::cout << "R)" << std::endl;
							else
									std::cout << "B)" << std::endl;
							level += 1;
							print_prefix(cur->left_child, level);
							print_prefix(cur->right_child, level);
					}
			}
			// constructors, destructor

			rbt() : _root(NULL), _nil(NULL), _cmp(key_cmp()), _alloc_rbt(alloc_node()), _size(0) //, unique_tree(unique_tree) rbt(status unique_tree)???
			{ 
				_nil = create_nil_node();
				// _root = _nil;
			}

			rbt(const rbt &x){
				_root = x._root;
				_nil = x._nil;
				_cmp = x._cmp;
				_alloc_rbt = x._alloc_rbt;
				_size = x._size;
			}

			~rbt(){	}

			rbt & operator=(const rbt &x)
			{
				_cmp = x._cmp;
				_alloc_rbt = x._alloc_rbt;
				_size = x._size;
				return (*this);
			}

			node_ref operator*(void) const{
				return (_root);
			}

			node_ptr operator->(void) const{
				return (&_root);
			}


			// setters

			void	setSize(size_t s)
			{
				_size = s;
			}

			void	setRoot(node_ptr root)
			{
				_root = root;
			}

			// getters

			size_t	getSize() const
			{
				return (_size);
			}

			size_t	getMaxsize() const
			{
				return (_alloc_rbt.max_size());
			}

			node_ptr	getRoot() const
			{
				return (_root);
			}

			iterator	begin() const
			{
				node_ptr tmp = getBegin(_root);
				return (iterator(tmp, NULL));
			}

			iterator	begin_mmap() const
			{
				node_ptr tmp = getRoot();
				return (iterator(tmp, NULL));
			}

			const_iterator	const_begin() const
			{
				node_ptr tmp = getBegin(_root);
				return (const_iterator(tmp, NULL));
			}

			node_ptr	getBegin(node_ptr tmp) const
			{
				if (!tmp){

					return (NULL);
				}
				while (tmp->left_child)
				{
					tmp = tmp->left_child;
				}
				return (tmp);
			}

			iterator	end() const
			{
				node_ptr tmp = getEnd(_root);
				return (iterator(NULL, tmp));
			}

			const_iterator	const_end() const
			{
				node_ptr tmp = getEnd(_root);
				return (const_iterator(NULL, tmp));
			}

			node_ptr	getEnd(node_ptr tmp) const
			{
				if (!tmp)
					return (NULL);
				
				while (tmp->right_child)
				{
					tmp = tmp->right_child;
				}
				return (tmp);
			}

			bool	empty()
			{
				if(_size == 0)
					return (1);
				return (0);
			}

			bool value_compare(const value_type& x, const value_type& y) const
			{
				return _cmp(x.first, y.first);
			}

			bool value_compare(const key_type& x, const key_type& y) const
			{
				return _cmp(x, y);
			}

			node_ptr	insert_fixup(node_ptr _node)
			{
				node_ptr	_parent = _node->parent;

				// std::cout << "fixup\n";
				// std::cout << " node = " << _node->pair.second << " " << _node->color << " parent = " << _parent->pair.second << " " << _parent->color << "\n";
				// if (_node->right_child)
				// 	std::cout << " child = " << _node->right_child->pair.second << " " << _node->right_child->color << "\n";
				// PB  : quid quand parent est la root : ca veut dire qu on ne reequilibre jamais dans ces cas la??
				// alors qu on devrait pouvoir (cf vizualiser)
				
				while (_node->parent && _node->parent->color == RED)
				{
					if (_node->parent->parent->left_child && _node->parent == _node->parent->parent->left_child)
					{
						_parent = _node->parent->parent->right_child;
						if (_node->parent->parent->right_child && _parent->color == RED)
						{
							_node->parent->color = BLACK;
							_parent->color = BLACK;
							_node->parent->parent->color = RED;
							_node = _node->parent->parent;
						}
						else 
						{
							if (_node == _node->parent->right_child)
							{
								_node = _node->parent;
								left_rotate(_node);
							}
							_node->parent->color = BLACK;
							_node->parent->parent->color = RED;
							right_rotate(_node->parent->parent);
						}
					}
					else
					{
						if (_node->parent == _node->parent->parent->right_child)
						{
							_parent = _node->parent->parent->left_child;
							if (_node->parent->parent->left_child && _parent->color == RED)
							{
								_node->parent->color = BLACK;
								_parent->color = BLACK;
								_node->parent->parent->color = RED;
								_node = _node->parent->parent;
							}
							else
							{
								if (_node == _node->parent->left_child)
								{
									_node = _node->parent;
									right_rotate(_node);
								}
								_node->parent->color = BLACK;
								_node->parent->parent->color = RED;
								left_rotate(_node->parent->parent);
							}
						}
					}
				}
				_root->color = BLACK;
				
				return (_node);
			}

			// add_node == insert a new node in a map
			ft::pair<iterator, bool>	add_node(const Type &p)
			{

				if (!_root){
					_root = _alloc_rbt.allocate(1);
					_alloc_rbt.construct(_root, node(p));
					_root->color = BLACK;
					_root->parent = NULL;
					_size++;
					return (ft::make_pair<iterator, bool>(iterator(_root, NULL), true));
				}
				node_ptr	tmp = _root;
				node_ptr	tmp_parent = NULL;

				while (tmp)
				{
					tmp_parent = tmp;
					if (value_compare(p, tmp->pair))
					{
						tmp = tmp->left_child;
					}
					else if (value_compare(tmp->pair, p))
					{
						tmp = tmp->right_child;
					}
					else
					{
						return (ft::make_pair<iterator, bool>(iterator(tmp, NULL), false));
					}
				}
				tmp = _alloc_rbt.allocate(1);
				_alloc_rbt.construct(tmp, node(p));
				tmp->color = RED;
				tmp->parent = tmp_parent;
				if (value_compare(tmp_parent->pair, tmp->pair))
					tmp_parent->right_child = tmp;
				else
					tmp_parent->left_child = tmp;
				_size++;
				insert_fixup(tmp);
				return (ft::make_pair<iterator, bool>(iterator(tmp, NULL), true));
			}

			// insert a new node in a multimap
			iterator	add_node_mmap(const value_type &p)
			{
				if (!_root){
					_root = _alloc_rbt.allocate(1);
					_alloc_rbt.construct(_root, node(p));
					_root->color = BLACK;
					_root->parent = NULL;
					_size++;
					return (iterator(_root, NULL));
				}
				node_ptr	tmp = _root;
				node_ptr	tmp_parent = NULL;

				while (tmp)
				{
					tmp_parent = tmp;
					if (value_compare(p, tmp->pair))
					{
						tmp = tmp->left_child;
					}
					else if (value_compare(tmp->pair, p))
					{
						tmp = tmp->right_child;
					}
					else
					{
						// s il y a plsrs nodes avec la meme cle, aller jusqu'au dernier
								// std::cout << "coucou1\n";
						if (tmp->right_child)
						{
							// tq qu il y a des nodes avec la meme cle en left_child:
							while (tmp && tmp->right_child)
							{
								if (tmp->pair.first == tmp->right_child->pair.first)
								{
									// std::cout << "iech1 \n";
									tmp = tmp->left_child;
								
									node_ptr newtmp = tmp->right_child;
									newtmp = _alloc_rbt.allocate(1);
									_alloc_rbt.construct(newtmp, node(p));
									newtmp->color = RED;
									newtmp->parent = tmp;
									tmp->right_child = newtmp;

									_size++;
									insert_fixup(newtmp);
									return (iterator(newtmp, NULL));

								}
								else if (tmp->pair.first != tmp->right_child->pair.first)
								{
									// std::cout << "iech2 \n";
									tmp = tmp->right_child;								
									node_ptr newtmp = tmp->right_child;
									newtmp = _alloc_rbt.allocate(1);
									_alloc_rbt.construct(newtmp, node(p));
									newtmp->color = RED;
									newtmp->parent = tmp;
									if (value_compare(tmp->pair, newtmp->pair))
										tmp->right_child = newtmp;
									else
										tmp->left_child = newtmp;
									_size++;
									insert_fixup(newtmp);
									return (iterator(newtmp, NULL));

								}

								// manquerait le cas ou il y a deja un node a l emplacement du node equivalent
								// donc penser a le decaler pour faire l insertion
								// + possible pb quand meme key que l ordre ne soit pas respecte
								// (mais possible aussi que ce ne soit pas un pb, si c undefined)
								// ce qui est etrae c que normalement le nouveau node equivalent est mis comme enfant
								// et au final il a l ngair d etre parent a chaque fois 
							}
						}
						// std::cout << "tmp " << tmp->pair.first << " " << tmp->pair.second << "\n";
						// std::cout << "tmp_parent " << tmp->parent->pair.first<< " " << tmp->parent->pair.second << "\n"; 
						// if (tmp->left_child)
						// 	std::cout << "tmp_child " << tmp->left_child->pair.first << " " << tmp->left_child->pair.second << "\n";
						// std::cout << "iech3 \n";
						// creer un nouveau node
						tmp = _alloc_rbt.allocate(1);
						_alloc_rbt.construct(tmp, node(p));
						tmp->color = RED;
						tmp->parent = tmp_parent;
						// if (value_compare(tmp_parent->pair, tmp->pair))
							tmp_parent->right_child = tmp;
						// else
						// 	tmp_parent->left_child = tmp;
						_size++;
						insert_fixup(tmp);
						return (iterator(tmp, NULL));
					}
				}
				
				tmp = _alloc_rbt.allocate(1);
				_alloc_rbt.construct(tmp, node(p));
				tmp->color = RED;
				tmp->parent = tmp_parent;
				if (value_compare(tmp_parent->pair, tmp->pair))
					tmp_parent->right_child = tmp;
				else
					tmp_parent->left_child = tmp;
				_size++;
				insert_fixup(tmp);
				return (iterator(tmp, NULL));
			}

			void 	fix_mmap(node_ptr tmp)
			{
				node_ptr other_tmp = tmp;
				node_ptr nil_l = _nil->left_child;
				node_ptr nil_r = _nil->right_child;

				if ((_nil->left_child != _nil && (value_compare(other_tmp->pair, nil_l->pair))) || other_tmp->pair == nil_l->pair) 
				{
					nil_l = getBegin(other_tmp);
				}
				if ((_nil->right_child != _nil && (value_compare(other_tmp->pair, nil_l->pair))) || other_tmp->pair == nil_r->pair) // || value_compare()) > || KeyOfValue()(nodeNode->value) == KeyOfValue()(nilLeft->value))))
				{
					nil_l = getBegin(other_tmp);
				}
			}

			iterator	insert_newnode_mmap(node_ptr tmp)
			{
				std::cout << "tmp " << tmp->pair.first << "\n";
				std::cout << "nil " << _nil->pair.first << "\n";
				// fix_mmap(tmp);

				if (_nil->left_child ==  _nil)
				{
					// std::cout << "coucou1\n";
					_nil->left_child = tmp;

				}
				if (_nil->right_child == _nil)
				{
					// std::cout << "coucou2\n";
					_nil->right_child = tmp;
				}
				insert_fixup(tmp);
				return iterator(tmp, NULL);
			}

			node_ptr	create_nil_node()
			{
				node_ptr nil_node = _alloc_rbt.allocate(1);
				
				nil_node->color = BLACK;
				nil_node->left_child = nil_node;
				nil_node->right_child = nil_node;
				nil_node->parent = nil_node;

    			return nil_node;
			}

			// insertion et equilibre

			void left_rotate(node_ptr x)
			{
				node_ptr y = x->right_child;

				x->right_child = y->left_child;
				if (y->left_child)
					y->left_child->parent = x;
				
				y->parent = x->parent;

				// if x is root, y becomes root
				if (!x->parent)
					_root = y;

				// else replace x by x
				else if (x == x->parent->left_child)
					x->parent->left_child = y;
				else
					x->parent->right_child = y;

				// x tied at y's left
				y->left_child = x;
				x->parent = y;
			}

			void right_rotate(node_ptr x)
			{
				node_ptr y = x->left_child;
				x->left_child = y->right_child;
				if (y->right_child)
					y->right_child->parent = x;
				
				y->parent = x->parent;
				if (!x->parent)
					_root = y;

				else if (x == x->parent->right_child)
					x->parent->right_child = y;
				else
					x->parent->left_child = y;

				y->right_child = x;
				x->parent = y;
			}



			iterator	find(const key_type &x) const
			{
				node_ptr tmp = _root;

				if (!tmp)
					return (end());
				while (tmp)
				{
					// std::cout << "tmp = " << tmp->pair.first << " " << tmp->pair.second << "\n";
					if (value_compare(x, tmp->pair.first))
					{
						// std::cout << "tmp1 = " << tmp->pair.first << " " << tmp->pair.second << "\n";
						tmp = tmp->left_child;
					}
					else if (value_compare(tmp->pair.first, x))
					{
						// std::cout << "tmp2 = " << tmp->pair.first << " " << tmp->pair.second << "\n";
						tmp = tmp->right_child;
					}
					else
					{
						// std::cout << "tmp3 = " << tmp->pair.first << " " << tmp->pair.second << "\n";
						return (iterator(tmp, tmp->parent));
					}
				}
				std::cout << "prout\n";
				return (end());

			}

			const_iterator	const_find(const key_type &x) const
			{
				node_ptr tmp = _root;

				if (!tmp)
					return (const_end());
				while(tmp)
				{
					if (value_compare(x, tmp->pair.first))
						tmp = tmp->left_child;
					else if (value_compare(tmp->pair.first, x))
						tmp = tmp->right_child;
					else
						return (const_iterator(tmp, tmp->parent));
				}
				return (const_iterator(tmp, tmp->parent));

			}

			iterator	lower_bound(const key_type & x) const
			{
				iterator	tmp_b = begin();
				iterator	tmp_e = end();

				for (;tmp_b != tmp_e; tmp_b++)
				{
					if (!(value_compare(tmp_b->first, x)))
						return (tmp_b);
				}
				
				return (tmp_b);
			}

			const_iterator	const_lower_bound(const key_type & x)
			{
				const_iterator	tmp_b = begin();
				const_iterator	tmp_e = end();

				for (;tmp_b != tmp_e; tmp_b++)
				{
					if (!(value_compare(tmp_b->first, x)))
						return (tmp_b);
				}
				
				return (tmp_b);
			}

			iterator	upper_bound(const key_type & x) const
			{
				iterator	tmp_b = begin();
				iterator	tmp_e = end();

				for (;tmp_b != tmp_e; tmp_b++)
				{
					if (value_compare(x, tmp_b->first))
						return (tmp_b);
				}
				
				return (tmp_b);
			}

			const_iterator	const_upper_bound(const key_type & x)
			{
				const_iterator	tmp_b = begin();
				const_iterator	tmp_e = end();

				for (;tmp_b != tmp_e; tmp_b++)
				{
					if (value_compare(x, tmp_b->first))
						return (tmp_b);
				}
				
				return (tmp_b);
			}

			void	clear()
			{
				_root = destroy_rbt(_root);
			}

			node_ptr	destroy_rbt(node_ptr rbt_node)
			{
				if (!rbt_node)
					return NULL;
				if (rbt_node->left_child)
					destroy_rbt(rbt_node->left_child);
				if (rbt_node->right_child)
					destroy_rbt(rbt_node->right_child);
				_alloc_rbt.destroy(rbt_node);
				_alloc_rbt.deallocate(rbt_node, 1);
				_size = 0;
				return NULL;
			}


			void	rbt_transplant(node_ptr x, node_ptr y)
			{
				if (!x->parent)
					_root = y;
				else if (x == x->parent->left_child)
					x->parent->left_child = y;
				else
					x->parent->right_child = y;

				if (y)
					y->parent = x->parent;
			}

			// fcts for erasing a pair

			size_type	erase(const key_type& x)
			{
				node_ptr	tmp_b = getRoot();
				node_ptr	tmp_y = NULL;
				node_ptr	tmp_x = NULL;
				
				while (tmp_b && tmp_b->pair.first != x)
				{
					if (tmp_b && value_compare(x, tmp_b->pair.first))
						tmp_b = tmp_b->left_child;
					else if (tmp_b && value_compare(tmp_b->pair.first, x))
						tmp_b = tmp_b->right_child;
				}

				if (!tmp_b)
					return (0);
				
				tmp_y = tmp_b;
				int tmp_color = tmp_y->color;				

				if (!tmp_b->left_child)
				{
					tmp_x = tmp_b->right_child;
					rbt_transplant(tmp_b, tmp_b->right_child);
				}
				else if (!tmp_b->right_child)
				{
					tmp_x = tmp_b->left_child;
					rbt_transplant(tmp_b, tmp_b->left_child);
				}
				else
				{
					tmp_y = getBegin(tmp_b->right_child);
					tmp_color = tmp_y->color;
					tmp_x = tmp_y->right_child;
					if (tmp_x && tmp_y->parent == tmp_b)
						tmp_x->parent = tmp_y;
					else
					{
						rbt_transplant(tmp_y, tmp_y->right_child);
						tmp_y->right_child = tmp_b->right_child;
						if (tmp_y->right_child)
							tmp_y->right_child->parent = tmp_y;
					}
					rbt_transplant(tmp_b, tmp_y);
					tmp_y->left_child = tmp_b->left_child;
					tmp_y->left_child->parent = tmp_y;
					tmp_y->color = tmp_b->color;
				}
				if (tmp_x)
					std::cout << " tmp_x= " << tmp_x->pair.first << " " << tmp_x->pair.second;
				if (tmp_color == BLACK && tmp_x)
					delete_rbt_fixup(tmp_x);

				if (tmp_b)
					std::cout << " tmp = " << tmp_b->pair.first << " " << tmp_b->pair.second << "\n";
				_alloc_rbt.destroy(tmp_b);
				_alloc_rbt.deallocate(tmp_b, 1);
				_size--;
				return (1);
			}

			size_type	erase_mmap(const key_type& x)
			{
				node_ptr	tmp_b = getRoot();
				node_ptr	tmp = getBegin(tmp_b);
				node_ptr	tmp_y = NULL;
				node_ptr	tmp_x = NULL;
				
				// pb : il ne trouve pas les children de root dans la boucle (apparemment null ?!?)
				// alors qu ils sont bien dans le rbt

				while (tmp_b)
				{
					// std::cout << " tmpb = " << tmp_b->pair.first << " " << tmp_b->pair.second << "\n";
					// if (tmp_b->right_child)
					// 	std::cout << " tmpb_rightchild = " << tmp_b->right_child->pair.first << " " << tmp_b->right_child->pair.second << "\n";
					// if (tmp_b->left_child)
					// 	std::cout << " tmpb_leftchild = " << tmp_b->left_child->pair.first << " " << tmp_b->left_child->pair.second << "\n";
					if (tmp->pair.first == x)
					{
						tmp_b = tmp;
						break;
					}
					if (tmp_b && value_compare(x, tmp_b->pair.first))
						tmp_b = tmp_b->left_child;
					else if (tmp_b && value_compare(tmp_b->pair.first, x))
						tmp_b = tmp_b->right_child;
					else if (tmp_b->right_child && tmp_b->left_child && (tmp_b->right_child->pair.first == x || tmp_b->left_child->pair.first == x))
					{
						if (tmp_b->right_child->pair.first == x)
							tmp_b = tmp_b->right_child;
						else
							tmp_b = tmp_b->left_child;
						// std::cout << "tmp_b = " << tmp_b->pair.first << " " << tmp_b->pair.second << "\n";
						if (!tmp_b->left_child && !tmp_b->right_child)
							break;
					}
					
				}
				
				if (!tmp_b)
					return (0);
				
				tmp_y = tmp_b;
				int tmp_color = tmp_y->color;				

				if (!tmp_b->left_child)
				{
					tmp_x = tmp_b->right_child;
					rbt_transplant(tmp_b, tmp_b->right_child);
				}
				else if (!tmp_b->right_child)
				{
					tmp_x = tmp_b->left_child;
					rbt_transplant(tmp_b, tmp_b->left_child);
				}
				else
				{
					tmp_y = getBegin(tmp_b->right_child);
					tmp_color = tmp_y->color;
					tmp_x = tmp_y->right_child;
					if (tmp_x && tmp_y->parent == tmp_b)
						tmp_x->parent = tmp_y;
					else
					{
						rbt_transplant(tmp_y, tmp_y->right_child);
						tmp_y->right_child = tmp_b->right_child;
						if (tmp_y->right_child)
							tmp_y->right_child->parent = tmp_y;
					}
					rbt_transplant(tmp_b, tmp_y);
					tmp_y->left_child = tmp_b->left_child;
					tmp_y->left_child->parent = tmp_y;
					tmp_y->color = tmp_b->color;
				}
				// if (tmp_x)
				// 	std::cout << " tmp_x= " << tmp_x->pair.first << " " << tmp_x->pair.second;
				if (tmp_color == BLACK && tmp_x)
					delete_rbt_fixup(tmp_x);

				_alloc_rbt.destroy(tmp_b);
				_alloc_rbt.deallocate(tmp_b, 1);
				_size--;
				return (1);
			}

			void	delete_rbt_fixup(node_ptr x)
			{
				node_ptr	w = NULL;
				while (x != _root && x->color == BLACK)
				{
					if (x == x->parent->left_child)
					{
						w = x->parent->right_child;
						if (w->color== RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent);
							w = x->parent->right_child;
						}
						if (w->left_child->color == BLACK && w->right_child->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->right_child->color == BLACK)
							{
								w->left_child->color = BLACK;
								w->color = RED;
								right_rotate(w);
								w = x->parent->right_child;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right_child->color = BLACK;
							left_rotate(x->parent);
							x = _root;
						}	
					}
					else
					{
						w = x->parent->left_child;
						if (w->color== RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent);
							w = x->parent->left_child;
						}
						if (w->right_child->color == BLACK && w->left_child->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->right_child->color == BLACK)
							{
								w->right_child->color = BLACK;
								w->color = RED;
								right_rotate(w);
								w = x->parent->left_child;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left_child->color = BLACK;
							left_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
			}

			void	swap(rbt & x)
			{
				node_ptr tmp_root = x._root;
				key_cmp tmp_cmp = x._cmp;
				AllocNode tmp_alloc_rbt = x._alloc_rbt;
				size_t tmp_size = x._size;

				x._root = _root;
				x._cmp = _cmp;
				x._alloc_rbt = _alloc_rbt;
				x._size = _size;

				_root = tmp_root;
				_cmp = tmp_cmp;
				_alloc_rbt = tmp_alloc_rbt;
				_size = tmp_size;
			}
    };
}

#endif