#include "algorithm.hpp"
#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <vector>

Test(vector_erase, erase_begin)
{
	ft::vector<int> v(10, 42);
	ft::vector<int>::iterator result;
	int old_size;

	old_size = v.size();

	result = v.erase(v.begin());

	cr_expect_eq(v.size(), old_size - 1);
	cr_expect_eq(result, v.begin());

	result = v.erase(v.end() - 1);
	cr_expect_eq(result, v.end());
}

Test(vector_erase, erase_last)
{
	ft::vector<int> v;
	ft::vector<int>::iterator result;
	int old_size;

	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	old_size = v.size();
	result = v.erase(v.end() - 1);

	cr_expect_eq(v.size(), old_size - 1);
	cr_expect_eq(v[v.size() - 1], v.size() - 1);
}

Test(vector_erase, erase_range)
{
	ft::vector<int> v;
	ft::vector<int>::iterator result;
	int old_size;
	const int n = 3;

	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	old_size = v.size();
	result = v.erase(v.begin(), v.begin() + n);

	cr_expect_eq(v.size(), old_size - n);
	cr_expect_eq(v[0], n);
}

Test(vector_erase, should_not_effect_capacity)
{
	ft::vector<int> v(10, 42);
	int old_cap;

	old_cap = v.capacity();

	v.erase(v.begin(), v.end());

	cr_expect_eq(v.capacity(), old_cap);

	v.assign(100, 42);
	old_cap = v.capacity();

	v.erase(v.begin() + 10);

	cr_expect_eq(v.capacity(), old_cap);
}
