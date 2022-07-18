#include "criterion/assert.h"
#include "stack.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <deque>

Test(stack_cnst, empty_stack)
{
	ft::stack<int> s;

	cr_expect(s.empty());
}

Test(stack_cnst, copy_container_stack)
{
	ft::vector<int> v(10, 1);
	v.push_back(42);

	ft::stack<int> s(v);

	cr_expect_not(s.empty());
	cr_expect_eq(v.size(), s.size());
	cr_expect_eq(v.back(), s.top());
}

Test(stack_cnst, copy_stack)
{
	ft::vector<int> v(10, 1);
	v.push_back(42);

	ft::stack<int> s(v);
	ft::stack<int> copy(s);

	cr_expect_eq(s.size(), copy.size());
	cr_expect_eq(s.top(), copy.top());
}

Test(stack_cnst, construct_by_std_container)
{
	std::deque<int> dq(10, 1);
	dq.push_back(42);

	ft::stack<int, std::deque<int> > s(dq);

	cr_expect_eq(s.size(), dq.size());
	cr_expect_eq(s.top(), dq.back());

	s.pop();
	dq.pop_back();
	cr_expect_eq(s.top(), dq.back());
}
