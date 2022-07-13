#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <iterator>
#include <memory>
#include <vector>

Test(vector_cnst, default_construct)
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

Test(vector_cnst, fill_constructor)
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

Test(vector_cnst, fill_constructor_by_zero)
{
	ft::vector<int> v(0);

	criterion::logging::info << "cap: " << v.capacity() << ", size: " << v.size() << std::flush;
	cr_expect_eq(v.begin(), v.end());
	cr_expect_eq(v.size(), 0);
	cr_expect_eq(v.capacity(), 0);
}

Test(vector_cnst, copy_construct)
{
	ft::vector<int> v;

	v.push_back(10);
	criterion::logging::info << "v[0]: " << v[0] << std::flush;
	criterion::logging::info << "cap: " << v.capacity() << ", size: " << v.size() << std::flush;

	v.push_back(42);
	criterion::logging::info << "cap: " << v.capacity() << ", size: " << v.size() << std::flush;
	criterion::logging::info << "origin: " << v[0] << ", " << v[1] << std::flush;

	ft::vector<int> copy(v);

	cr_expect_eq(v.size(), copy.size());
	cr_expect_eq(v.capacity(), copy.capacity());

	cr_expect_eq(v[1], copy[1]);

	criterion::logging::info << "test deep copy" << std::flush;
	v[1] = 0;
	cr_expect_neq(v[1], copy[1]);
}

Test(vector_cnst, range_constructor)
{
	const int n = 5;
	std::vector<int> v_iter = {1, 2, 3, 4, 5};
	const int p_iter[n] = {1, 2, 3, 4, 5};

	ft::vector<int> v1(v_iter.begin(), v_iter.end());
	ft::vector<int> v2(p_iter, p_iter + n);

	cr_expect_eq(v1.size(), n);
	cr_expect_eq(v1.size(), v2.size());
	cr_expect_eq(v1[0], v2[0]);
	cr_expect_eq(v1[n - 1], v2[n - 1]);
}
