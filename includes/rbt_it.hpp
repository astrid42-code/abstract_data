#ifndef RBT_IT_HPP
#define RBT_IT_HPP

#include <iostream>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "rev_it.hpp"
#include "bi_directional_it.hpp"

namespace ft
{
	template< typename node, class Compare >
	class rbt_const_it;

	template< typename node, class Compare >
	class rbt_it : public ft::iterator<std::bidirectional_iterator_tag, typename node::value_type>
	{
		
		public:
			typedef node * 														node_ptr;
			typedef typename 	node::value_type								value_type;
			typedef ft::iterator<std::bidirectional_iterator_tag, value_type>	iterator;
			typedef typename iterator::iterator_category						iterator_category;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::pointer									pointer;
			typedef typename iterator::reference								reference;

		private:
			node_ptr	_node;
			node_ptr	_parent;

		public:
		
			// constructors :

			rbt_it() : _node(NULL), _parent(NULL) {}

			rbt_it(node_ptr x, node_ptr y) : _node(x), _parent(y) {}
			
			rbt_it(const rbt_it &x) : _node(x._node), _parent(x._parent) {}

			~rbt_it() {}

			rbt_it & operator=(const rbt_it &op)
			{
				_node = op._node;
				_parent = op._parent;
				return (*this);
			}

			node_ptr	get_node() const
			{
				return (_node);
			}

			node_ptr	get_parent() const
			{
				return (_parent);
			}

			reference operator*() const 
			{
				return (_node->pair);
			}
				
			// 'The mutable iterator can be dereferenced as lvalue
			pointer operator->() const 
			{
				return (&operator*());
			}

			// operators

			bool	operator==(const rbt_it &it) const
			{
				return (_node == it._node);
			}

			bool	operator!=(const rbt_it &it) const
			{
				return !(*this == it);
			}

			rbt_it&	operator++()
			{
				if (_node)
				{
					_parent = _node;
					
					if (_node->right_child)
					{
						_node = _node->right_child;
						while (_node->left_child)
							_node = _node->left_child;
					}
					else
					{
						while (_node->parent && _node == _node->parent->right_child)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return (*this);
			}

			rbt_it	operator++(int) 
			{
				rbt_it	tmp = *this;
				++(*this);
				return (tmp);
			}

			rbt_it&	operator--()
			{
				if (_node)
				{
					_parent = _node;
					if (_node->left_child)
					{
						_node = _node->left_child;
						while (_node->right_child)
							_node = _node->right_child;
					}
					else
					{
						while (_node->parent && _node == _node->parent->left_child)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else
					_node = _parent;
				return (*this);
			}

			rbt_it	operator--(int)
			{
				rbt_it	tmp = *this;
				--(*this);
				return (tmp);
			}
    };

	template< typename node, class Compare >
	class rbt_const_it : public ft::iterator<std::bidirectional_iterator_tag, typename node::value_type>
	{
		
		public:
			typedef node * 														node_ptr;
			typedef typename node::value_type const								value_type;
			typedef ft::iterator<std::bidirectional_iterator_tag, value_type>	iterator;
			typedef typename iterator::iterator_category						iterator_category;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::pointer									pointer;
			typedef typename iterator::reference								reference;
		
		private:
			node_ptr	_node;
			node_ptr	_parent;
		
		public:

			rbt_const_it() : _node(), _parent() {}

			rbt_const_it(node_ptr x, node_ptr y) : _node(x), _parent(y) {}

			rbt_const_it(const rbt_const_it<node, Compare> &x)
			{
				_node = x._node;
				_parent = x._parent;
			}

			rbt_const_it(const rbt_it<node, Compare> &c_it)
			{
				_node = c_it.get_node();
				_parent = c_it.get_parent();
			} 

			~rbt_const_it() {}

			rbt_const_it & operator=(const rbt_const_it &op)
			{
				_node = op._node;
				_parent = op._parent;
				return (*this);
			}

			node_ptr	base() const 
			{
				return (_node);
			}

			node_ptr	get_node() const
			{
				return (_node());
			}

			node_ptr	get_parent() const
			{
				return (_parent);
			}

			reference operator*() const 
			{
				return (_node->pair);
			}
				
			// 'The mutable iterator can be dereferenced as lvalue
			pointer operator->() const 
			{
				return (&operator*());
			}

			// operators

			bool	operator==(const rbt_const_it &it) const
			{
				return (_node == it._node);
			}

			bool	operator!=(const rbt_const_it &it) const
			{
				return !(*this == it);
			}

			rbt_const_it&	operator++()
			{
				if (_node)
				{
					_parent = _node;
					if (_node->right_child)
					{
						_node = _node->right_child;
						while (_node->left_child)
							_node = _node->left_child;
					}
					else
					{
						while (_node->parent && _node == _node->parent->right_child)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return (*this);
			}

			rbt_const_it	operator++(int)
			{
				rbt_const_it	tmp = *this;
				++(*this);
				return (tmp);
			}

			rbt_const_it&	operator--()
			{
				if (_node)
				{
					_parent = _node;
					if (_node->left_child)
					{
						_node = _node->left_child;
						while (_node->right_child)
							_node = _node->right_child;
					}
					else
					{
						while (_node->parent && _node == _node->parent->left_child)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else
					_node = _parent;
				return (*this);
			}

			rbt_const_it	operator--(int)
			{
				rbt_const_it	tmp = *this;
				--(*this);
				return (tmp);
			}
			
    };

	template< typename node, class Compare >
	std::ostream & operator<<(std::ostream & o, rbt_it<node, Compare> const & max_op)
	{
		o << max_op.get_node()->pair;
		return (o);
	}
}

#endif