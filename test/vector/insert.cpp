#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_insert, insert_single_element_to_empty_vector)
{
	ft::vector<int> v;
	const int value = 42;

	v.insert(v.begin(), value);
	cr_expect_eq(*v.begin(), value);
	cr_expect_eq(v.size(), 1);
}

Test(vector_insert, insert_single_element_at_middle_of_vector)
{
	ft::vector<int> v(10, 1);
	const int value = 42;
	int old_size = v.size();

	v.insert(v.begin() + 5, value);
	cr_expect_eq(*(v.begin() + 5), value);
	cr_expect_eq(v.size(), old_size + 1);
}
