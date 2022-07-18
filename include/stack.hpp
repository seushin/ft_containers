#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template<class T, class Container = vector<T> >
class stack
{
protected:
	Container c;

public:
	// clang-format off
	typedef Container                      container_type;
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type  size_type;
	// clang-format on

	stack();
	stack(const stack &other);
	explicit stack(const Container &c);

	stack &operator=(const stack &rhs);

	~stack();

	bool empty() const;
	size_type size() const;
	value_type &top();
	const value_type &top() const;
	void push(const value_type &val);
	void pop();

	template<class T1, class C1>
	friend bool operator==(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs);

	template<class T1, class C1>
	friend bool operator<(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs);
};

template<class T, class Container>
stack<T, Container>::stack() : c()
{}

template<class T, class Container>
stack<T, Container>::stack(const stack &other) : c(other.c)
{}

template<class T, class Container>
stack<T, Container>::stack(const Container &x) : c(x)
{}

template<class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(const stack &rhs)
{
	c = rhs.c;
	return (*this);
}

template<class T, class Container>
stack<T, Container>::~stack()
{}

template<class T, class Container>
bool stack<T, Container>::empty() const
{
	return (c.size() == 0);
}

template<class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const
{
	return (c.size());
}

template<class T, class Container>
typename stack<T, Container>::value_type &stack<T, Container>::top()
{
	return (c.back());
}

template<class T, class Container>
const typename stack<T, Container>::value_type &stack<T, Container>::top() const
{
	return (c.back());
}

template<class T, class Container>
void stack<T, Container>::push(const value_type &val)
{
	c.push_back(val);
}

template<class T, class Container>
void stack<T, Container>::pop()
{
	c.pop_back();
}

template<class T1, class C1>
bool operator==(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
{
	return (lhs.c == rhs.c);
}

template<class T1, class C1>
bool operator!=(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
{
	return (!(lhs == rhs));
}

template<class T1, class C1>
bool operator<(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
{
	return (lhs.c < rhs.c);
}

template<class T1, class C1>
bool operator<=(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
{
	return (!(rhs < lhs));
}

template<class T1, class C1>
bool operator>(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
{
	return (rhs < lhs);
}

template<class T1, class C1>
bool operator>=(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs)
{
	return (!(lhs < rhs));
}

} // namespace ft

#endif // !STACK_HPP
