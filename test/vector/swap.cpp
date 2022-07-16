#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(vector_swap, should_be_different_size)
{
	ft::vector<int> a(10, 42);
	ft::vector<int> b(42, 10);
	int old_a_size, old_b_size;

	old_a_size = a.size();
	old_b_size = b.size();

	a.swap(b);

	cr_expect_eq(a.size(), old_b_size);
	cr_expect_eq(b.size(), old_a_size);
}

Test(vector_swap, should_refer_swapped_obj)
{
	ft::vector<int> a(10, 42);
	ft::vector<int> b(42, 10);
	ft::vector<int>::iterator old_a, old_b;

	old_a = a.begin();
	old_b = b.begin();

	a.swap(b);

	cr_expect_eq(a.begin(), old_b);
	cr_expect_eq(b.begin(), old_a);
}

Test(vector_swap, call_global_swap)
{
	ft::vector<int> a(10, 42);
	ft::vector<int> b(42, 10);
	ft::vector<int>::iterator old_a, old_b;

	old_a = a.begin();
	old_b = b.begin();

	swap(a, b);

	cr_expect_eq(a.begin(), old_b);
	cr_expect_eq(b.begin(), old_a);
}
