#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "iterator/category.hpp"
#include "util/enable_if.hpp"
#include <cstddef>

namespace ft
{

template<class Iter>
struct iterator_traits
{
	// clang-format off
	typedef typename Iter::value_type        value_type;
	typedef typename Iter::difference_type   difference_type;
	typedef typename Iter::pointer           pointer;
	typedef typename Iter::reference         reference;
	typedef typename Iter::iterator_category iterator_category;
	// clang-format on
};

template<class T>
struct iterator_traits<T *>
{
	// clang-format off
	typedef random_access_iterator_tag iterator_category;
	typedef std::ptrdiff_t             difference_type;
	typedef T                          value_type;
	typedef T*                         pointer;
	typedef T&                         reference;
	// clang-format on
};

// template<class T>
// struct iterator_traits<const T *>
// {
// 	// clang-format off
// 	typedef random_access_iterator_tag iterator_category;
// 	typedef std::ptrdiff_t             difference_type;
// 	typedef const T                    value_type;
// 	typedef const T*                   pointer;
// 	typedef const T&                   reference;
// 	// clang-format on
// };

} // namespace ft

#endif // !ITERATOR_TRAITS_HPP
