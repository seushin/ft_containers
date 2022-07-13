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

} // namespace ft

#endif // !UTIL_HPP
