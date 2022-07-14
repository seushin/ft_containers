#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_pop_back, pop_back_basic)
{
	ft::vector<int> v(10, 42);
	ft::vector<int>::iterator begin, end;
	int old_size, old_cap;

	begin = v.begin();
	end = v.end();
	old_size = v.size();
	old_cap = v.capacity();

	v.pop_back();

	cr_expect_eq(v.begin(), begin);
	cr_expect_neq(v.end(), end);
	cr_expect_eq(v.size(), old_size - 1);
	cr_expect_eq(v.capacity(), old_cap);
}
