#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_pb, push_back_basic)
{
	ft::vector<int> v;
	const int n = 5;

	for (int i = 0; i < n; ++i)
		v.push_back(i);
	criterion::logging::info << "cap: " << v.capacity() << ", size: " << v.size() << std::flush;

	cr_expect_eq(v[0], 0);
	cr_expect_eq(v[n - 1], n - 1);
	cr_expect_eq(v.size(), n);
}

Test(vector_pb, push_back_repeat)
{
	ft::vector<int> v;
	const int n = 5000000;

	for (int i = 0; i < n; ++i)
		v.push_back(i);
	criterion::logging::info << "cap: " << v.capacity() << ", size: " << v.size() << std::flush;

	cr_expect_eq(v[0], 0);
	cr_expect_eq(v[n - 1], n - 1);
	cr_expect_eq(v.size(), n);
}
