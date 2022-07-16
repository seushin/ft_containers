#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_pop_back, should_decrease_size)
{
	ft::vector<int> v(10, 42);
	int old_size;

	old_size = v.size();

	v.pop_back();

	cr_expect_eq(v.size(), old_size - 1);
}

Test(vector_pop_back, should_not_change_capacity)
{
	ft::vector<int> v(10, 42);
	int old_cap;

	old_cap = v.capacity();

	v.pop_back();

	cr_expect_eq(v.capacity(), old_cap);
}

Test(vector_pop_back, should_keep_referring_other_element)
{
	ft::vector<int> v(10, 42);
	ft::vector<int>::iterator begin, end;

	begin = v.begin();
	end = v.end();

	v.pop_back();

	cr_expect_eq(v.begin(), begin);
	cr_expect_neq(v.end(), end);
}
