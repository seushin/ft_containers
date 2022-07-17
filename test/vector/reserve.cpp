#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(vector_reserve, should_no_effect_on_size)
{
	ft::vector<int> v(10);
	int old_size;

	old_size = v.size();
	v.reserve(42);

	cr_expect_eq(v.size(), old_size);
}

Test(vector_reserve, should_no_effect_on_element)
{
	ft::vector<int> v(10, 42);
	int old_value;

	old_value = v.front();
	v.reserve(42);

	cr_expect_eq(v.front(), old_value);
}

Test(vector_reserve, should_be_reallocate)
{
	ft::vector<int> v;
	ft::vector<int>::iterator begin;
	const int cap = 42;

	begin = v.begin();
	v.reserve(cap);

	cr_expect_neq(begin, v.begin());
	cr_expect_eq(v.capacity(), cap);
}

Test(vector_reserve, should_not_allocate_if_less)
{
	ft::vector<int> v(42);
	ft::vector<int>::iterator begin;
	const int cap = 10;

	begin = v.begin();
	v.reserve(cap);

	cr_expect_eq(begin, v.begin());
	cr_expect_neq(v.capacity(), cap);
}
