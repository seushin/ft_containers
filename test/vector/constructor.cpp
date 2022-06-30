#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <cstddef>
#include <memory>
#include <vector>

Test(vector, default_construct)
{
	ft::vector<int> v;

	cr_expect_eq(v.size(), 0);
	cr_fail("to be eq: v.begin(), v.end()");
}

Test(vector, fill_constructor)
{
	const int n = 10;
	const int val = 42;
	ft::vector<int> v(n, val);

	cr_expect_eq(v.size(), n);
	cr_fail("v[n - 1], val");
}

Test(vector, copy_construct)
{
	ft::vector<int> v;

	v.push_back(10);
	v.push_back(42);

	ft::vector<int> copy(v);
	cr_expect_eq(v.size(), copy.size());
	cr_expect_eq(v[1], copy[1]);
}

Test(vector, range_constructor)
{
	std::vector<int> v_iter = {1, 2, 3, 4, 5};
	const int p_iter[] = {1, 2, 3, 4, 5};
	cr_fail("ft::vector<int> v1(v_iter.begin(), v_iter.end());");
	cr_fail("ft::vector<int> v2(p_iter.begin(), p_iter.end());");
	cr_fail("to be eq: v1, v2");
}
