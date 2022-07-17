#ifndef SPLIT_BUFFER_HPP
#define SPLIT_BUFFER_HPP

#include "algorithm.hpp"
#include "iterator/iterator_traits.hpp"
#include "util/enable_if.hpp"
#include "util/is_integral.hpp"
#include <memory>

namespace ft
{

template<class T, class Allocator = std::allocator<T> >
class split_buffer
{
private:
	split_buffer(const split_buffer &);
	split_buffer &operator=(const split_buffer &);

public:
	// clang-format off
	typedef T                                        value_type;
	typedef Allocator                                allocator_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::size_type        size_type;
	// clang-format on

	pointer begin_;
	pointer end_;
	pointer end_cap_;
	allocator_type alloc_;

	split_buffer();
	split_buffer(size_type new_size, allocator_type &alloc);
	~split_buffer();
	size_type capacity() const;

	void push(size_type n);
	void push(size_type n, const_reference val);
	template<class InputIterator>
	void push(
			InputIterator first,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last);
	void destroy_at_end_(pointer new_end);
	size_type recommend_size_(size_type new_size) const;
};

template<class T, class Allocator>
split_buffer<T, Allocator>::split_buffer() : begin_(0), end_(0), end_cap_(0), alloc_()
{}

template<class T, class Allocator>
split_buffer<T, Allocator>::split_buffer(size_type new_size,
										 allocator_type &alloc)
	: begin_(0), end_(0), end_cap_(0), alloc_(alloc)
{
	if (new_size > 0)
	{
		begin_ = end_ = alloc_.allocate(new_size);
		end_cap_ = begin_ + new_size;
	}
}

template<class T, class Allocator>
split_buffer<T, Allocator>::~split_buffer()
{
	destroy_at_end_(begin_);
	alloc_.deallocate(begin_, capacity());
}

template<class T, class Allocator>
typename split_buffer<T, Allocator>::size_type split_buffer<T, Allocator>::capacity() const
{
	return (static_cast<size_type>(end_cap_ - begin_));
}

template<class T, class Allocator>
void split_buffer<T, Allocator>::push(size_type n)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; pos != new_end; ++pos)
	{
		alloc_.construct(pos);
	}
}

template<class T, class Allocator>
void split_buffer<T, Allocator>::push(size_type n, const_reference val)
{
	const_pointer new_end = end_ + n;

	for (pointer &pos = end_; pos != new_end; ++pos)
	{
		alloc_.construct(pos, val);
	}
}

template<class T, class Allocator>
template<class InputIterator>
void split_buffer<T, Allocator>::push(
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
void split_buffer<T, Allocator>::destroy_at_end_(pointer new_end)
{
	while (new_end != end_)
	{
		alloc_.destroy(--end_);
	}
}

} // namespace ft

#endif // !SPLIT_BUFFER_HPP
