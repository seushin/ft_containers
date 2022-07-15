#ifndef IS_ITERATOR_HPP
#define IS_ITERATOR_HPP

#include "iterator/category.hpp"
#include "iterator/iterator_traits.hpp"

namespace ft
{

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

template<class T>
struct has_iterator_category
{
private:
	struct two
	{
		char one;
		char two;
	};
	template<class U>
	static char test(typename U::iterator_category * = 0);
	template<class U>
	static two test(U * = 0);

public:
	static const bool value = sizeof(test<T>(0)) == 1;
};

template<bool, class T>
struct is_iterable_base : public false_type
{};

template<class T>
struct is_iterable_base<true, T> : public true_type
{};

template<class T>
struct is_iterable : public is_iterable_base<has_iterator_category<T>::value, T>
{};

template<class T>
struct is_input_iterator : public is_iterable<T>
{};

} // namespace ft

#endif // !IS_ITERATOR_HPP
