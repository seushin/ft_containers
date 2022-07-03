#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator/iterator_traits.hpp"
#include <memory>
#include <stdexcept>

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
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	// element access
	reference operator[](size_type n);
	const_reference operator[](size_type n) const;

	// capacity
	size_type size() const;
	size_type max_size() const;
	size_type capacity() const;

	// modifiers
	void push_back(const value_type &val);

private:
	iterator begin_;
	iterator end_;
	iterator end_cap_;
	allocator_type alloc_;

private:
	void allocate_(size_type n);
	void deallocate_();
	void construct_(size_type n);
	void construct_(size_type n, const_reference val);
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
{
	if (n > 0)
	{
		allocate_(n);
		construct_(n);
	}
}

template<class T, class Allocator>
vector<T, Allocator>::vector(size_type n, const value_type &val)
{
	if (n > 0)
	{
		allocate_(n);
		construct_(n, val);
	}
}

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

// iterators
template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin()
{
	return (begin_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end()
{
	return (end_);
}

// element access
template<class T, class Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::operator[](size_type n)
{
	// FIXME

	return (begin_[n]);
}

// capacity
template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
{
	// FIXME
	return (end_ - begin_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const
{
	return (alloc_.max_size());
}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const
{
	return (0);
}

// modifiers
template<class T, class Allocator>
void vector<T, Allocator>::push_back(const value_type &val)
{
	// FIXME
	// allocate & insert element
}

// private member function
template<class T, class Allocator>
void vector<T, Allocator>::allocate_(size_type n)
{
	if (n > max_size())
		throw std::length_error("ft::vector");
	begin_ = end_ = alloc_.allocate(n);
	end_cap_ = end_ + n;
}

template<class T, class Allocator>
void vector<T, Allocator>::deallocate_()
{
	if (begin_ != 0)
	{
		// destroy
		alloc_.deallocate(begin_, capacity());
	}
	begin_ = end_ = end_cap_ = 0;
}

template<class T, class Allocator>
void vector<T, Allocator>::construct_(size_type n)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; end_ != new_end; ++pos)
	{
		alloc_.construct(pos);
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::construct_(size_type n, const_reference val)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; end_ != new_end; ++pos)
	{
		alloc_.construct(pos, val);
	}
}

} // namespace ft

#endif // !VECTOR_HPP
