#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "iterator/iterator_traits.hpp"
#include "util/enable_if.hpp"
#include "util/is_integral.hpp"
#include <iostream>

namespace ft
{

template<class T>
void swap(T &a, T &b)
{
	T c(a);

	a = b;
	b = c;
}

template<class T>
T &min(T &a, T &b)
{
	return (a < b ? a : b);
}

template<class T>
T max(T a, T b)
{
	return (a < b ? b : a);
}

template<class T>
T &max(T &a, T &b)
{
	return (a < b ? b : a);
}

template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	typename iterator_traits<InputIterator>::difference_type d = 0;

	for (; first != last; ++first)
		++d;
	return (d);
}

template<class InputIterator>
InputIterator
copy(InputIterator first,
	 InputIterator last,
	 typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type dest)
{
	for (; first != last; ++first, ++dest)
	{
		*dest = *first;
	}
	return (dest);
}

template<class InputIterator1>
bool equal(InputIterator1 first1,
		   InputIterator1 last1,
		   typename enable_if<!is_integral<InputIterator1>::value, InputIterator1>::type first2)
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (*first1 != *first2)
			return (false);
	}
	return (true);
}

template<class T, class U>
struct less
{
	bool operator()(const T &a, const U &b) const
	{
		return (a < b);
	}
};

template<class T, class U>
struct greater
{
	bool operator()(const T &a, const U &b) const
	{
		return (b < a);
	}
};

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(
		InputIterator1 first1,
		typename enable_if<!is_integral<InputIterator1>::value, InputIterator1>::type last1,
		InputIterator2 first2,
		typename enable_if<!is_integral<InputIterator2>::value, InputIterator2>::type last2)
{
	for (; first2 != last2; ++first1, ++first2)
	{
		if (first1 == last1 || *first1 < *first2)
			return (true);
		if (*first2 < *first1)
			return (false);
	}
	return (false);
}

} // namespace ft

#endif // !ALGORITHM_HPP
