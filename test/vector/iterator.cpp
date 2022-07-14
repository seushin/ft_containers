#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(vector_iter, should_refer_expected)
{
	ft::vector<int> v;
	ft::vector<int>::iterator begin, end;

	v.push_back(1);
	v.push_back(42);

	begin = v.begin();
	end = v.end();

	cr_expect_eq(*begin++, v[0]);
	cr_expect_eq(*begin, v[1]);
}

Test(vector_iter, should_iterate_by_size)
{
	ft::vector<int> v(10, 42);
	ft::vector<int>::iterator begin, end;
	int count = 0;

	begin = v.begin();
	end = v.end();

	for (; begin != end; ++begin)
		count++;

	cr_expect_eq(count, v.size());
}

Test(vector_iter, has_const_iterator)
{
	const int value = 42;
	const ft::vector<int> v(10, value);
	ft::vector<int>::const_iterator begin, end;

	begin = v.begin();
	end = v.end();

	for (; begin != end; ++begin)
		cr_expect_eq(*begin, value);
}
