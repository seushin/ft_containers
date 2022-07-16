#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{

template<bool, class T = void>
struct enable_if
{};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

struct false_type
{
	static const bool value = false;
};

struct true_type
{
	static const bool value = true;
};

template<class T, class U>
struct is_same : public false_type
{};

template<class T>
struct is_same<T, T> : public true_type
{};

} // namespace ft

#endif // !ENABLE_IF_HPP
