#ifndef TREE_HPP
#define TREE_HPP

namespace ft
{

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

struct tree_iterator
{};

struct tree_const_iterator
{};

template<class T, class Compare, class Allocator>
class tree
{
public:
	// clang-format off
	typedef T         value_type;
	typedef Compare   value_compare;
	typedef Allocator allocator_type;

	typedef tree_node<T> node;
	typedef node         *node_pointer;
	// clang-format on

	tree();
	tree(const tree &other);
	tree &operator=(const tree &rhs);
	~tree();

private:
	node base_;

	node_pointer root() const
	{
		return (base_.left);
	}
};

template<class T, class Compare, class Allocator>
tree<T, Compare, Allocator>::tree() : base_() {}

} // namespace ft

#endif // !TREE_HPP
