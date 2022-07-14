#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(vector_resize, should_destruct)
{
	ft::vector<int> v(10, 42);
	const int new_size = 5;

	v.resize(new_size, 0);

	cr_expect_eq(v.size(), new_size);
}

Test(vector_resize, should_construct)
{
	ft::vector<int> v(10, 42);
	const int new_size = 15;
	const int new_value = 21;
	int old_cap;

	v.reserve(20);
	old_cap = v.capacity();

	v.resize(new_size, new_value);

	cr_expect_eq(v.size(), new_size);
	cr_expect_eq(v.capacity(), old_cap);
	cr_expect_eq(v[10], new_value);
}

Test(vector_resize, should_not_anything)
{
	ft::vector<int> v(10, 42);
	const int new_size = 10;
	const int new_value = 21;
	int old_cap, old_size;

	old_cap = v.capacity();
	old_size = v.size();
	v.resize(new_size, new_value);

	cr_expect_eq(v.size(), old_size);
	cr_expect_eq(v.capacity(), old_cap);
	cr_expect_neq(v[9], new_value);
}
