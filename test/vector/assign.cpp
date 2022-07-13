#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <list>

Test(vector_assign, assign_range_by_iter)
{
	ft::vector<int> v(10, 42);
	ft::vector<int> target(5, 0);

	target.assign(v.begin(), v.end());

	cr_expect_eq(v.size(), target.size());
	cr_expect_eq(v[0], target[0]);
	cr_expect_eq(v[9], target[9]);
}

Test(vector_assign, assign_range_by_std_iter)
{
	ft::vector<int> target;
	std::list<int> li(10, 42);

	target.assign(li.begin(), li.end());

	cr_expect_eq(target.size(), li.size());
	cr_expect_eq(target[0], li.front());
	cr_expect_eq(target[9], li.back());
}

Test(vector_assign, assign_range_by_pointer)
{
	const int n = 5;
	ft::vector<int> target;
	int arr[n] = {1, 2, 3, 4, 5};

	target.assign(arr, arr + n);

	cr_expect_eq(target.size(), n);
	cr_expect_eq(target[0], arr[0]);
	cr_expect_eq(target[n - 1], arr[n - 1]);
}

Test(vector_assign, assign_fill)
{
	ft::vector<int> v(10, 42);
	ft::vector<int> target;

	target.assign(10, 42);
	cr_expect_eq(v, target);
}
