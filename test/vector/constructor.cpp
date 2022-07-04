#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <iterator>
#include <memory>
#include <vector>

Test(vector, default_construct)
{
	ft::vector<int> v;
	std::vector<int> origin;

	criterion::logging::info << "std::vector default construct: size=" << origin.size()
							 << " capacity=" << origin.capacity() << std::flush;
	criterion::logging::info << "ft::vector default construct: size=" << v.size()
							 << " capacity=" << v.capacity() << std::flush;
	cr_expect_eq(v.size(), 0);
	cr_expect_eq(v.capacity(), 0);
	cr_expect_eq(v.begin(), v.end());
}

Test(vector, fill_constructor)
{
	const int n = 10;
	const int val = 42;
	ft::vector<int> v(n, val);
	ft::vector<int> v_default_val(n);
	std::vector<int> origin(n);

	criterion::logging::info << "std::vector construct with size: size=" << origin.size()
							 << " capacity=" << origin.capacity() << std::flush;
	criterion::logging::info << "ft::vector construct with size: size=" << v_default_val.size()
							 << " capacity=" << v_default_val.capacity() << std::flush;
	cr_expect_eq(v.size(), n);
	cr_expect_eq(v_default_val.size(), n);
	cr_expect_eq(v[n - 1], val);
	cr_expect_eq(v_default_val[n - 1], int());
}

Test(vector, copy_construct)
{
	ft::vector<int> v;

	v.push_back(10);
	v.push_back(42);

	ft::vector<int> copy(v);

	cr_expect_eq(v.size(), copy.size());
	cr_expect_eq(v.capacity(), copy.capacity());

	cr_expect_eq(v[1], copy[1]);

	v[1] = 0;
	cr_expect_neq(v[1], copy[1]);
}

Test(vector, range_constructor)
{
	std::vector<int> v_iter = {1, 2, 3, 4, 5};
	const int p_iter[] = {1, 2, 3, 4, 5};
	cr_fail("ft::vector<int> v1(v_iter.begin(), v_iter.end());");
	cr_fail("ft::vector<int> v2(p_iter.begin(), p_iter.end());");
	cr_fail("to be eq: v1, v2");
}
