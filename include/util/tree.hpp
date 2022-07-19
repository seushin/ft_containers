#ifndef TREE_HPP
#define TREE_HPP

namespace ft
{

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
