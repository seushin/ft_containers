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

	*begin = 0;
	cr_expect_eq(v[0], 0);

	cr_expect_eq(begin + v.size(), end);
}

Test(vector_iter, iterator_iteration)
{
	const int n = 10;
	ft::vector<int> v;
	ft::vector<int>::iterator begin, end;

	for (int i = 0; i < n; ++i)
		v.push_back(i);

	begin = v.begin();
	end = v.end();

	int i = 0;
	for (ft::vector<int>::iterator it = begin; it != end; ++it)
	{
		cr_expect_eq(*it, i);
		i++;
	}
	cr_expect_eq(i, v.size());
}

Test(vector_iter, const_iterator_basic)
{
	const ft::vector<int> v(10, 42);
	ft::vector<int>::const_iterator begin, end;

	begin = v.begin();
	end = v.end();

	cr_expect_eq(*begin, v[0]);
	cr_expect_eq(begin + v.size(), end);
}
