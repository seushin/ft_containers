#ifndef SPLIT_BUFFER_HPP
#define SPLIT_BUFFER_HPP

#include "util.hpp"
#include <iostream>
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

	allocator_type alloc_;
	pointer start_;
	pointer begin_;
	pointer end_;
	pointer end_cap_;

	split_buffer();
	split_buffer(size_type new_size, size_type old_size, allocator_type &alloc);
	~split_buffer();
	size_type capacity() const;

	void construct_at_end_(size_type n);
	void construct_at_end_(size_type n, const_reference val);
	void construct_at_front_(pointer b, pointer e, size_type n);
	void destroy_at_end_(pointer new_end);
	size_type recommend_size_(size_type new_size) const;
};

template<class T, class Allocator>
split_buffer<T, Allocator>::split_buffer() : start_(0), begin_(0), end_(0), end_cap_(0), alloc_()
{}

template<class T, class Allocator>
split_buffer<T, Allocator>::split_buffer(size_type new_size,
										 size_type old_size,
										 allocator_type &alloc)
	: alloc_(alloc)
{
	if (new_size > 0)
	{
		start_ = alloc_.allocate(new_size);
		begin_ = end_ = start_ + old_size;
		end_cap_ = start_ + new_size;
	}
}

template<class T, class Allocator>
split_buffer<T, Allocator>::~split_buffer()
{
	destroy_at_end_(start_);
	alloc_.deallocate(start_, capacity());
}

template<class T, class Allocator>
typename split_buffer<T, Allocator>::size_type split_buffer<T, Allocator>::capacity() const
{
	return (static_cast<size_type>(end_cap_ - start_));
}

template<class T, class Allocator>
void split_buffer<T, Allocator>::construct_at_end_(size_type n)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; end_ != new_end; ++pos)
	{
		alloc_.construct(pos);
	}
}

template<class T, class Allocator>
void split_buffer<T, Allocator>::construct_at_end_(size_type n, const_reference val)
{
	const_pointer new_end = end_ + n;
	for (pointer &pos = end_; end_ != new_end; ++pos)
	{
		alloc_.construct(pos, val);
	}
}

template<class T, class Allocator>
void split_buffer<T, Allocator>::construct_at_front_(pointer b, pointer e, size_type n)
{
	// TODO
	/*
	if (start_ == end_)
	{
		for (pointer p = b; p != e; ++p)
			construct_at_end_(1, *p);
	}
	else
	{
		for (pointer p = b, cur = start_; p != e; ++p, ++cur)
		{
			alloc_.construct(cur, *p);
		}
	}
	*/
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
