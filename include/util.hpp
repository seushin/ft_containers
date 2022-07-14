#ifndef UTIL_HPP
#define UTIL_HPP

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
T &max(T &a, T &b)
{
	return (a < b ? b : a);
}

} // namespace ft

#endif // !UTIL_HPP
