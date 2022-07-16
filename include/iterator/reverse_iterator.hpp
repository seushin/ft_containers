#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template<class Iter>
class reverse_iterator
{
private:
	Iter iter_;

public:
	// clang-format off
	typedef Iter                                              iterator_type;
	typedef typename iterator_traits<Iter>::iterator_category iterator_category;
	typedef typename iterator_traits<Iter>::difference_type   value_type;
	typedef typename iterator_traits<Iter>::difference_type   difference_type;
	typedef typename iterator_traits<Iter>::reference         reference;
	typedef typename iterator_traits<Iter>::pointer           pointer;
	// clang-format on

	reverse_iterator() : iter_() {}
	reverse_iterator(iterator_type iter) : iter_(iter) {}
	reverse_iterator(const reverse_iterator &other) : iter_(other.iter_) {}
	reverse_iterator &operator=(const reverse_iterator &rhs)
	{
		iter_ = rhs.iter_;
		return (*this);
	}
	~reverse_iterator() {}

	iterator_type base() const
	{
		return (iter_);
	}

	reference operator*() const {}
	pointer operator->() const {}
	reference operator[](difference_type n) const {}
	reverse_iterator &operator+=(difference_type n) {}
	reverse_iterator operator+(difference_type n) {}
	reverse_iterator &operator++() {}
	reverse_iterator operator++(int) {}
	reverse_iterator &operator-=(difference_type n) {}
	reverse_iterator operator-(difference_type n) {}
	reverse_iterator &operator--() {}
	reverse_iterator operator--(int) {}
};

template<class Iter>
bool operator==(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{}

template<class Iter>
bool operator!=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{
	return (!(lhs == rhs));
}

template<class Iter>
bool operator<(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{}

template<class Iter>
bool operator<=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{
	return (!(rhs < lhs));
}

template<class Iter>
bool operator>(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{
	return (rhs < lhs);
}

template<class Iter>
bool operator>=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{
	return (!(lhs < rhs));
}

template<class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &rev_it)
{}

template<class Iter>
typename reverse_iterator<Iter>::difference_type
operator-(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
{}

} // namespace ft

#endif // !REVERSE_ITERATOR_HPP
