#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_iter, iterator_basic)
{
	ft::vector<int> v(10, 42);
	ft::vector<int>::iterator begin, end;

	begin = v.begin();
	end = v.end();
	cr_expect_eq(*begin, v[0]);
	cr_expect_eq(begin + v.size(), end);
}
