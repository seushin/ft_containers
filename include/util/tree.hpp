#ifndef TREE_HPP
#define TREE_HPP

#include "iterator/category.hpp"
#include "util/pair.hpp"
#include <cstddef>

namespace ft
{

template<class T>
struct select_first
{
	typedef T type;
};

template<class Key, class T>
struct select_first<pair<Key, T> >
{
	typedef Key type;
};

template<class NodePtr>
NodePtr tree_min_node(NodePtr x)
{
	while (x != 0 && x->left != 0)
		x = x->left;
	return (x);
}

template<class NodePtr>
NodePtr tree_max_node(NodePtr x)
{
	while (x != 0 && x->right != 0)
		x = x->right;
	return (x);
}

template<class NodePtr>
NodePtr tree_next_node(NodePtr x)
{
	if (x->right != 0)
		return tree_min_node(x->right);

	NodePtr parent = x->parent;

	while (parent != 0 && parent->right == x)
	{
		x = parent;
		parent = x->parent;
	}
	return (parent);
}

template<class NodePtr>
NodePtr tree_prev_node(NodePtr x)
{
	if (x->left != 0)
		return tree_max_node(x->right);

	NodePtr parent = x->parent;

	while (parent != 0 && parent->left == x)
	{
		x = parent;
		parent = x->parent;
	}
	return (parent);
}

template<class NodePtr>
void tree_insert(NodePtr root, NodePtr x)
{
	NodePtr parent = 0;
	NodePtr current = root;

	while (current)
	{
		parent = current;

		if (x->value == current->value)
			return;
		else if (x->value < current->value)
			current = current->left;
		else
			current = current->right;
	}

	x->parent = parent;
	if (parent == 0)
		root->parent->left = x;
	else if (x->value < parent->value)
		parent->left = x;
	else
		parent->right = x;
}

template<class NodePtr>
void tree_transplant_node(NodePtr root, NodePtr x, NodePtr y)
{
	if (x->parent == 0)
		root->parent->left = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	if (y != 0)
		y->parent = x->parent;
}

template<class NodePtr>
void tree_remove(NodePtr root, NodePtr x)
{
	if (x->left == 0)
		tree_transplant_node(root, x, x->right);
	else if (x->right == 0)
		tree_transplant_node(root, x, x->left);
	else
	{
		NodePtr y = tree_min_node(x->right);

		if (y->parent != x)
		{
			tree_transplant_node(root, y, y->right);
			y->right = x->right;
			y->right->parent = y;
		}
		tree_transplant_node(root, x, y);
		y->left = x->left;
		y->left->parent = y;
	}
}

struct tree_node_base
{
	tree_node_base *parent;
	tree_node_base *left;
	tree_node_base *right;

	tree_node_base() : parent(0), left(0), right(0) {}
	tree_node_base(const tree_node_base &x) : parent(x.parent), left(x.left), right(x.right) {}
	tree_node_base &operator=(const tree_node_base &rhs)
	{
		parent = rhs.parent;
		left = rhs.left;
		right = rhs.right;
		return (*this);
	}
	~tree_node_base() {}
};

template<class T>
struct tree_node : public tree_node_base
{
	typedef T value_type;

	value_type value;

	tree_node() : tree_node_base(), value() {}
	tree_node(const value_type &val) : tree_node_base(), value(val) {}
	tree_node(const tree_node &x) : tree_node_base(x), value(x.value) {}
	tree_node &operator=(const tree_node &rhs)
	{
		tree_node_base::operator=(rhs);
		value = rhs.value;
		return (*this);
	}
	~tree_node();
};

template<class T, class DiffType = std::ptrdiff_t>
class tree_iterator
{
public:
	// clang-format off
	typedef bidirectional_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef DiffType                   difference_type;
	typedef value_type&                reference;
	typedef value_type*                pointer;

private:
	typedef tree_node_base*            node_base_pointer;
	typedef tree_node<T>*              node_pointer;
	// clang-format on

	node_base_pointer iter_;

public:
	tree_iterator() : iter_(0) {}
	tree_iterator(const node_pointer p) : iter_(p) {}
	tree_iterator(const tree_iterator &x) : iter_(x.iter_) {}
	tree_iterator &operator=(const tree_iterator &rhs)
	{
		iter_ = rhs.iter_;
		return (*this);
	}
	~tree_iterator() {}

	value_type operator*() const
	{
		return (static_cast<node_pointer>(iter_)->value);
	}

	pointer operator->() const
	{
		return (&(operator*()));
	}

	tree_iterator &operator++()
	{
		iter_ = tree_next_node(iter_);
		return (*this);
	}

	tree_iterator operator++(int)
	{
		tree_iterator copy(*this);

		++(*this);
		return (copy);
	}

	tree_iterator &operator--()
	{
		iter_ = tree_prev_node(iter_);
		return (*this);
	}

	tree_iterator operator--(int)
	{
		tree_iterator copy(*this);

		--(*this);
		return (copy);
	}

	friend bool operator==(const tree_iterator &lhs, const tree_iterator &rhs)
	{
		return (lhs.iter_ == rhs.iter_);
	}

	friend bool operator!=(const tree_iterator &lhs, const tree_iterator &rhs)
	{
		return (!(lhs == rhs));
	}
};

class tree_const_iterator
{
	// TODO
};

// for management base node memory
template<class T, class Allocator>
class tree_base
{
public:
	// clang-format off
	typedef T                                                     value_type;
	typedef Allocator                                             allocator_type;
	typedef tree_node<value_type>                                 node;
	typedef typename allocator_type::template rebind<node>::other node_allocator;
	typedef typename node_allocator::pointer                      node_pointer;
	// clang-format on

	tree_base() : node_alloc_()
	{
		begin_node_ = end_node_ = allocate_one_();
	}
	tree_base(const allocator_type &alloc) : node_alloc_(alloc)
	{
		begin_node_ = end_node_ = allocate_one_();
	}
	tree_base(const tree_base &x) : node_alloc_(x.node_alloc_) {}

	tree_base &operator=(const tree_base &rhs)
	{
		return (*this);
	}

	~tree_base()
	{
		deallocate_one_(end_node_);
	}

	node_pointer allocate_one_()
	{
		return (node_alloc_.allocate(1));
	}

	void deallocate_one_(node_pointer p)
	{
		node_alloc_.deallocate(p, 1);
	}

protected:
	node_allocator node_alloc_;
	node_pointer begin_node_;
	node_pointer end_node_;
};

template<class T, class Compare, class Allocator>
class tree : protected tree_base<T, Allocator>
{
private:
	// clang-format off
	typedef tree_base<T, Allocator>                  base_;
	typedef typename base_::node                     node;
	typedef typename base_::node_pointer             node_pointer;

public:
	typedef T                                        value_type;
	typedef Compare                                  value_compare;
	typedef Allocator                                allocator_type;
	typedef typename base_::node_allocator           node_allocator;
	typedef tree_iterator<value_type>                iterator;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type       size_type;

private:
	typedef typename select_first<value_type>::type  key_type;
	// clang-format on

	tree();
	tree(const tree &other);
	tree &operator=(const tree &rhs);
	~tree();

protected:
	node_pointer &root() const
	{
		return (this->end_node_->left);
	}

	node_pointer create_node(const value_type &val)
	{
		node_pointer new_node = this->allocate_one_();

		try
		{
			this->node_alloc_.construct(new_node, node(val));
		}
		catch (...)
		{
			this->deallocate_one_(new_node);
		}
		return (new_node);
	}

	void destroy_node(node_pointer x)
	{
		this->node_alloc_.destroy(x);
		this->deallocate_one_(x);
	}
};

template<class T, class Compare, class Allocator>
tree<T, Compare, Allocator>::tree() : base_()
{
	root() = 0;
}

template<class T, class Compare, class Allocator>
tree<T, Compare, Allocator>::tree(const tree &other) : base_(other)
{}

template<class T, class Compare, class Allocator>
tree<T, Compare, Allocator> &tree<T, Compare, Allocator>::operator=(const tree &rhs)
{
	// TODO: clear, copy
	return (*this);
}

template<class T, class Compare, class Allocator>
tree<T, Compare, Allocator>::~tree()
{
	// clear()
}

} // namespace ft

#endif // !TREE_HPP
