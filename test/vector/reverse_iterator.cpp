#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(vector_rev_iter, should_refer_expected)
{
	ft::vector<int> v;
	ft::vector<int>::reverse_iterator rbegin, rend;

	v.push_back(1);
	v.push_back(42);

	rbegin = v.rbegin();
	rend = v.rend();

	cr_expect_eq(*rbegin++, v[1]);
	cr_expect_eq(*rbegin, v[0]);
}

Test(vector_rev_iter, should_iterate_by_size)
{
	ft::vector<int> v(10, 42);
	ft::vector<int>::reverse_iterator rbegin, rend;
	int count = 0;

	rbegin = v.rbegin();
	rend = v.rend();

	for (; rbegin != rend; ++rbegin)
		count++;

	cr_expect_eq(count, v.size());
}

Test(vector_rev_iter, has_const_iterator)
{
	const int value = 42;
	const ft::vector<int> v(10, value);
	ft::vector<int>::const_reverse_iterator rbegin, rend;

	rbegin = v.rbegin();
	rend = v.rend();

	for (; rbegin != rend; ++rbegin)
		cr_expect_eq(*rbegin, value);
}

Test(vector_rev_iter, iter_to_const_iter)
{
	ft::vector<int> v(10);
	ft::vector<int>::reverse_iterator ritb = v.rbegin();
	ft::vector<int>::reverse_iterator rite;
	ft::vector<int>::const_reverse_iterator critb = v.rbegin();
	ft::vector<int>::const_reverse_iterator crite;

	rite = v.rend();
	crite = rite;

	*ritb = 42;

	cr_expect_eq(*ritb, *critb);
	cr_expect_eq(ritb, critb);
}
