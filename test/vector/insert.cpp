#include "vector.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>

Test(vector_insert, insert_single_element_to_empty_vector)
{
	ft::vector<int> v;
	ft::vector<int>::iterator pos;

	const int value = 42;

	criterion::logging::info << "before cap: " << v.capacity() << std::flush;
	pos = v.insert(v.begin(), value);
	criterion::logging::info << "after cap: " << v.capacity() << std::flush;

	cr_expect_eq(*v.begin(), value);
	cr_expect_eq(v.begin(), pos);
	cr_expect_eq(v.size(), 1);
}

Test(vector_insert, insert_single_element_at_middle_of_vector)
{
	ft::vector<int> v(10, 1);
	ft::vector<int>::iterator pos;
	int old_size = v.size();

	const int value = 42;

	criterion::logging::info << "before cap: " << v.capacity() << std::flush;
	pos = v.insert(v.begin() + 5, value);
	criterion::logging::info << "after cap: " << v.capacity() << std::flush;

	cr_expect_eq(*(v.begin() + 5), value);
	cr_expect_eq(v.begin() + 5, pos);
	cr_expect_eq(v.size(), old_size + 1);
}

Test(vector_insert, insert_fill_at_begin)
{
	ft::vector<int> v(10, 1);
	ft::vector<int>::iterator pos;
	int old_size = v.size();

	const int n = 420000;
	const int value = 42;

	v.insert(v.begin(), n, value);

	cr_expect_eq(v.size(), old_size + n);
	cr_expect_eq(*v.begin(), 42);

	pos = v.begin() + n;
	cr_expect_eq(*pos, 1);
	--pos;
	cr_expect_eq(*pos, 42);
}

Test(vector_insert, insert_by_ft_vector_iter)
{
	ft::vector<int> v(10, 1);
	ft::vector<int>::iterator pos;
	int old_size = v.size();

	const int n = 4242;
	const int value = 42;
	ft::vector<int> dist(n, value);

	v.insert(v.begin(), dist.begin(), dist.end());

	cr_expect_eq(v.size(), old_size + n);
	cr_expect_eq(*v.begin(), 42);

	pos = v.begin() + n;
	cr_expect_eq(*pos, 1);
	--pos;
	cr_expect_eq(*pos, 42);
}
