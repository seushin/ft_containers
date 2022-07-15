#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "iterator/iterator_traits.hpp"
#include "iterator/random_access_iterator.hpp"
#include "split_buffer.hpp"
#include "util/enable_if.hpp"
#include "util/is_integral.hpp"
#include <algorithm>
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
	typedef random_access_iterator<pointer>                     iterator;
	typedef random_access_iterator<const_pointer>               const_iterator;
	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef typename allocator_type::size_type                  size_type;
	// clang-format on

	vector();
	vector(const allocator_type &alloc);

	vector(size_type n);
	vector(size_type n, const value_type &val);

	template<class InputIterator>
	vector(InputIterator first,
		   typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last);

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
	void resize(size_type n, value_type val = value_type());
	size_type capacity() const;
	void reserve(size_type n);

	// modifiers
	template<class InputIterator>
	void assign(InputIterator first,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last);
	void assign(size_type n, const value_type &val);
	void push_back(const value_type &val);
	void pop_back();
	iterator insert(iterator position, const value_type &val);
	void insert(iterator position, size_type n, const value_type &val);
	template<class InputIterator>
	void insert(iterator position,
				InputIterator first,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);
	void clear();

private:
	pointer begin_;
	pointer end_;
	pointer end_cap_;
	allocator_type alloc_;

	// util functions
	void allocate_(size_type n);
	void destruct_and_deallocate_();
	void reallocate_(size_type n);
	void construct_at_end_(size_type n);
	void construct_at_end_(size_type n, const_reference val);
	template<class InputIterator>
	void construct_at_end_(
			InputIterator first,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last);
	void destroy_at_end_(pointer new_end);
	size_type recommend_size_(size_type new_size) const;
	void swap_split_buffer(split_buffer<T, Allocator> &buf);
};

template<class T, class Allocator>
vector<T, Allocator>::vector() : begin_(0), end_(0), end_cap_(0), alloc_()
{}

template<class T, class Allocator>
vector<T, Allocator>::vector(const allocator_type &alloc)
	: begin_(0), end_(0), end_cap_(0), alloc_(alloc)
{}

template<class T, class Allocator>
vector<T, Allocator>::vector(size_type n) : begin_(0), end_(0), end_cap_(0), alloc_()
{
	if (n > 0)
	{
		allocate_(n);
		construct_at_end_(n);
	}
}

template<class T, class Allocator>
vector<T, Allocator>::vector(size_type n, const value_type &val)
	: begin_(0), end_(0), end_cap_(0), alloc_()
{
	if (n > 0)
	{
		allocate_(n);
		construct_at_end_(n, val);
	}
}

template<class T, class Allocator>
template<class InputIterator>
vector<T, Allocator>::vector(
		InputIterator first,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
	: begin_(0), end_(0), end_cap_(0), alloc_()
{
	assign(first, last);
}

template<class T, class Allocator>
vector<T, Allocator>::vector(const vector &other) : begin_(0), end_(0), end_cap_(0), alloc_()
{
	*this = other;
}

template<class T, class Allocator>
vector<T, Allocator> &vector<T, Allocator>::operator=(const vector &rhs)
{
	if (this == &rhs)
		return (*this);

	alloc_ = rhs.alloc_;
	allocate_(rhs.capacity());

	size_type sz = rhs.size();
	for (size_type i = 0; i < sz; i++)
	{
		construct_at_end_(1, rhs[i]);
	}
	return (*this);
}

template<class T, class Allocator>
vector<T, Allocator>::~vector()
{
	destruct_and_deallocate_();
}

// iterators
template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin()
{
	return (begin_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const
{
	return (begin_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end()
{
	return (end_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const
{
	return (end_);
}

// element access
template<class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type n)
{
	return (begin_[n]);
}

template<class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type n) const
{
	return (begin_[n]);
}

// capacity
template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
{
	return (static_cast<size_type>(end_ - begin_));
}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const
{
	return (alloc_.max_size());
}

template<class T, class Allocator>
void vector<T, Allocator>::resize(size_type n, value_type val)
{
	size_type sz = size();
	if (n < sz)
	{
		destroy_at_end_(begin_ + n);
	}
	else if (n > sz)
	{
		reserve(n);
		construct_at_end_(n - sz, val);
	}
}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const
{
	return (static_cast<size_type>(end_cap_ - begin_));
}

template<class T, class Allocator>
void vector<T, Allocator>::reserve(size_type n)
{
	if (n > capacity())
	{
		split_buffer<T, Allocator> buf(n, 0, alloc_);

		buf.construct_at_end_(begin(), end());
		swap_split_buffer(buf);
	}
}

// modifiers

template<class T, class Allocator>
template<class InputIterator>
void vector<T, Allocator>::assign(
		InputIterator first,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
{
	clear();
	for (; first != last; ++first)
	{
		push_back(*first);
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::assign(size_type n, const value_type &val)
{
	if (n <= capacity())
	{
		size_type old_size = size();
		size_type new_size = min(old_size, n);

		for (size_type i = 0; i < new_size; ++i)
			begin_[i] = val;
		if (n > old_size)
			construct_at_end_(n - old_size, val);
		else
			destroy_at_end_(begin_ + n);
	}
	else
	{
		destruct_and_deallocate_();
		allocate_(recommend_size_(n));
		construct_at_end_(n, val);
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::push_back(const value_type &val)
{
	if (end_ == end_cap_)
		reserve(recommend_size_(capacity() + 1));
	construct_at_end_(1, val);
}

template<class T, class Allocator>
void vector<T, Allocator>::pop_back()
{
	destroy_at_end_(--end_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(iterator position, const value_type &val)
{
	size_type new_size = size() + 1;
	size_type old_size = static_cast<size_type>(ft::distance(begin(), position));

	if (new_size > capacity())
	{
		split_buffer<T, Allocator> buf(recommend_size_(new_size), old_size, alloc_);

		buf.construct_at_end_(1, val);
		buf.construct_at_end_(position, end());
		buf.copy_origin_element_(begin(), position);
		swap_split_buffer(buf);
		position = begin() + old_size;
	}
	else
	{
		vector tmp(position, end());

		destroy_at_end_(position.base());
		construct_at_end_(1, val);
		construct_at_end_(tmp.begin(), tmp.end());
	}
	return (position);
}

template<class T, class Allocator>
void vector<T, Allocator>::insert(iterator position, size_type n, const value_type &val)
{
	size_type new_size = size() + n;
	size_type old_size = static_cast<size_type>(ft::distance(begin(), position));

	if (new_size > capacity())
	{
		split_buffer<T, Allocator> buf(recommend_size_(new_size), old_size, alloc_);

		buf.construct_at_end_(n, val);
		buf.construct_at_end_(position, end());
		buf.copy_origin_element_(begin(), position);
		swap_split_buffer(buf);
	}
	else
	{
		vector tmp(position, end());

		destroy_at_end_(position.base());
		construct_at_end_(n, val);
		construct_at_end_(tmp.begin(), tmp.end());
	}
}

template<class T, class Allocator>
template<class InputIterator>
void vector<T, Allocator>::insert(
		iterator position,
		InputIterator first,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
{
	size_type new_size = size() + ft::distance(first, last);
	size_type old_size = static_cast<size_type>(ft::distance(begin(), position));

	if (new_size > capacity())
	{
		split_buffer<T, Allocator> buf(recommend_size_(new_size), old_size, alloc_);

		buf.construct_at_end_(first, last);
		buf.construct_at_end_(position, end());
		buf.copy_origin_element_(begin(), position);
		swap_split_buffer(buf);
	}
	else
	{
		vector tmp(position, end());

		destroy_at_end_(position.base());
		construct_at_end_(first, last);
		construct_at_end_(tmp.begin(), tmp.end());
	}
}

template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator position)
{
	iterator new_end;

	new_end = ft::copy(position + 1, end(), position);
	destroy_at_end_(new_end.base());

	return (position);
}

template<class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
{
	iterator new_end;

	new_end = ft::copy(first + 1, last, first);
	destroy_at_end_(new_end.base());

	return (first);
}

template<class T, class Allocator>
void vector<T, Allocator>::clear()
{
	destroy_at_end_(begin_);
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
void vector<T, Allocator>::destruct_and_deallocate_()
{
	if (begin_ != 0)
	{
		clear();
		alloc_.deallocate(begin_, capacity());
	}
	begin_ = end_ = end_cap_ = 0;
}

template<class T, class Allocator>
void vector<T, Allocator>::construct_at_end_(size_type n)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; pos != new_end; ++pos)
	{
		alloc_.construct(pos);
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::construct_at_end_(size_type n, const_reference val)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; pos != new_end; ++pos)
	{
		alloc_.construct(pos, val);
	}
}

template<class T, class Allocator>
template<class InputIterator>
void vector<T, Allocator>::construct_at_end_(
		InputIterator first,
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
{
	typename iterator_traits<InputIterator>::difference_type d = ft::distance(first, last);
	const_pointer new_end = end_ + d;
	for (pointer &pos = end_; pos != new_end; ++pos)
	{
		alloc_.construct(pos, *first);
		++first;
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::destroy_at_end_(pointer new_end)
{
	while (new_end != end_)
	{
		alloc_.destroy(--end_);
	}
}

template<class T, class Allocator>
void vector<T, Allocator>::swap_split_buffer(split_buffer<T, Allocator> &buf)
{
	ft::swap(begin_, buf.start_);
	ft::swap(end_, buf.end_);
	ft::swap(end_cap_, buf.end_cap_);
}

template<class T, class Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::recommend_size_(size_type new_size) const
{
	const size_type ms = max_size();
	if (new_size > ms)
		throw std::length_error("ft::vector");
	const size_type cap = capacity();
	if (cap >= ms / 2)
		return (ms);
	return (max(2 * cap, new_size));
}

} // namespace ft

#endif // !VECTOR_HPP
