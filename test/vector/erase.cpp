#include "algorithm.hpp"
#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <vector>

Test(vector_erase, should_erase_one)
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

Test(vector_erase, test_std_vector_erase)
{
	std::vector<int> v(10, 42);
	std::vector<int>::iterator result;
	int old_size;

	old_size = v.size();

	result = v.erase(v.begin());

	cr_expect_eq(v.size(), old_size - 1);
	cr_expect_eq(result, v.begin());

	result = v.erase(v.end() - 1);

	cr_expect_eq(v.size(), old_size - 2);
	cr_expect_eq(result, v.end());
}
