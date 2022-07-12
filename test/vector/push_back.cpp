#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_pb, push_back_basic)
{
	ft::vector<int> v;
	const int n = 5;

	for (int i = 0; i <= n; ++i)
		v.push_back(i);
	cr_expect_eq(v[0], 0);
	cr_expect_eq(v[n], n);
	cr_expect_eq(v.size(), n);
}

Test(vector_pb, push_back_repeat)
{
	ft::vector<int> v;
	const int n = 5000000;

	for (int i = 0; i <= n; ++i)
		v.push_back(i);
	cr_expect_eq(v[0], 0);
	cr_expect_eq(v[n], n);
	cr_expect_eq(v.size(), n);
}
