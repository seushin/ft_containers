#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator/iterator_traits.hpp"
#include <memory>

namespace ft
{

template<class T, class Allocator = std::allocator<T> >
class vector
{
public:
	// typedef
	// clang-format off
	typedef T                                                   value_type;
	typedef Allocator                                           allocator_type;
	typedef typename allocator_type::pointer                    pointer;
	typedef typename allocator_type::const_pointer              const_pointer;
	typedef typename allocator_type::reference                  reference;
	typedef typename allocator_type::const_reference            const_reference;
	typedef pointer                                             iterator;
	typedef const_pointer                                       const_iterator;
	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef typename allocator_type::size_type                  size_type;
	// clang-format on

	vector();
	vector(const allocator_type &alloc);
	vector(size_type n);
	vector(size_type n, const value_type &val);
	vector(const vector &other);
	vector &operator=(const vector &rhs);
	~vector();

	// iterators
	/*
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	*/

	// capacity
	size_type size() const;
	size_type max_size() const;

private:
	iterator begin_;
	iterator end_;
	iterator end_cap_;
	allocator_type alloc_;
};

template<class T, class Allocator>
vector<T, Allocator>::vector() : begin_(0), end_(0), end_cap_(0), alloc_()
{}

template<class T, class Allocator>
vector<T, Allocator>::vector(const allocator_type &alloc)
	: begin_(0), end_(0), end_cap_(0), alloc_(alloc)
{}

template<class T, class Allocator>
vector<T, Allocator>::vector(size_type n)
{}

template<class T, class Allocator>
vector<T, Allocator>::vector(size_type n, const value_type &val)
{}

template<class T, class Allocator>
vector<T, Allocator>::vector(const vector &other)
{}

template<class T, class Allocator>
vector<T, Allocator> &vector<T, Allocator>::operator=(const vector &rhs)
{
	return (*this);
}

template<class T, class Allocator>
vector<T, Allocator>::~vector()
{}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
{
	// FIXME
	return (-1);
}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const
{
	// FIXME
	return (-1);
}

} // namespace ft

#endif // !VECTOR_HPP
