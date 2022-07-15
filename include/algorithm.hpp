#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "iterator/iterator_traits.hpp"
#include "util/enable_if.hpp"
#include "util/is_iterator.hpp"
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
	 typename enable_if<is_input_iterator<InputIterator>::value, InputIterator>::type dest)
{
	for (; first != last; ++first, ++dest)
	{
		*dest = *first;
	}
	return (dest);
}

} // namespace ft

#endif // !ALGORITHM_HPP
