#ifndef IS_ITERATOR_HPP
#define IS_ITERATOR_HPP

#include "iterator/category.hpp"
#include "iterator/iterator_traits.hpp"

namespace ft
{

template<class T>
struct is_iterator_or_pointer : public has_iterator_category<T>
{
private:
	template<class U>
	static char test(typename iterator_traits<U>::iterator_category * = 0);

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
struct is_iterable : public is_iterable_base<is_iterator_or_pointer<T>::value, T>
{};

template<class T>
struct is_input_iterator : public is_iterable<T>
{};

} // namespace ft

#endif // !IS_ITERATOR_HPP
