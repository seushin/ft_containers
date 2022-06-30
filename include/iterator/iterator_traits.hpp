#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "util/enable_if.hpp"
#include "iterator/category.hpp"
#include <cstddef>

namespace ft
{

template<class Iter, bool>
struct iterator_traits_impl
{};

template<class Iter>
struct iterator_traits_impl<Iter, true>
{
	// clang-format off
	typedef typename Iter::value_type        value_type;
	typedef typename Iter::difference_type   difference_type;
	typedef typename Iter::pointer           pointer;
	typedef typename Iter::reference         reference;
	typedef typename Iter::iterator_category iterator_category;
	// clang-format on
};

template<class Iter>
struct iterator_traits : public iterator_traits_impl<Iter, true /* TODO: use enable_if */>
{};

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

} // namespace ft

#endif // !ITERATOR_TRAITS_HPP
