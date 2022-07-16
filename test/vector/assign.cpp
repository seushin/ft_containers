#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <list>

Test(vector_assign, should_change_size_correctly)
{
	ft::vector<int> target(100, 0);
	ft::vector<int> v(10, 42);
	int old_size;

	old_size = target.size();
	target.assign(v.begin(), v.end());

	cr_expect_neq(target.size(), old_size);
	cr_expect_eq(target.size(), v.size());
}

Test(vector_assign, call_by_iter)
{
	ft::vector<int> target(5, 0);
	ft::vector<int> v(10, 42);

	target.assign(v.begin(), v.end());

	cr_expect_eq(v.size(), target.size());
	cr_expect_eq(v[0], target[0]);
	cr_expect_eq(v[9], target[9]);
}

Test(vector_assign, call_by_std_iter)
{
	ft::vector<int> target;
	std::list<int> li(10, 42);

	target.assign(li.begin(), li.end());

	cr_expect_eq(target.size(), li.size());
	cr_expect_eq(target[0], li.front());
	cr_expect_eq(target[9], li.back());
}

Test(vector_assign, call_by_pointer)
{
	ft::vector<int> target;
	const int n = 5;
	int arr[n] = {1, 2, 3, 4, 5};

	target.assign(arr, arr + n);

	cr_expect_eq(target.size(), n);
	cr_expect_eq(target[0], arr[0]);
	cr_expect_eq(target[n - 1], arr[n - 1]);
}

Test(vector_assign, call_by_size_and_value)
{
	ft::vector<int> target(100, 0);
	const int n = 10;
	const int value = 42;

	target.assign(n, value);

	criterion::logging::info << "target[0]: " << target[0] << std::flush;
	cr_expect_eq(target.size(), n);
	cr_expect_eq(target[0], value);
	cr_expect_eq(target[n - 1], value);
}
