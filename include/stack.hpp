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

} // namespace ft

#endif // !STACK_HPP
