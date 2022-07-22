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
	// clang-format on
};

} // namespace ft

#endif // !TREE_HPP
