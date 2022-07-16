#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(vector_relational_op, should_be_equal)
{
	ft::vector<int> a, b;
	ft::vector<int> c(10, 42), d(10, 42);

	cr_expect_eq(a, b);
	cr_expect_eq(c, d);
}

Test(vector_relational_op, should_not_equal)
{
	ft::vector<int> a, b(1);
	ft::vector<int> c(10, 42), d(10, 43);

	cr_expect_neq(a, b);
	cr_expect_neq(c, d);
}

Test(vector_relational_op, should_be_greater)
{
	ft::vector<int> a, b(1);
	ft::vector<int> c(10, 42), d(10, 43);

	cr_expect(a < b);
	cr_expect(c < d);
}
