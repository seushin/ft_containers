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
	typedef typename iterator_traits<Iter>::value_type        value_type;
	typedef typename iterator_traits<Iter>::difference_type   difference_type;
	typedef typename iterator_traits<Iter>::reference         reference;
	typedef typename iterator_traits<Iter>::pointer           pointer;
	// clang-format on

	reverse_iterator() : iter_() {}
	reverse_iterator(iterator_type iter) : iter_(iter) {}
	template<class Iter2>
	reverse_iterator(const reverse_iterator<Iter2> &other) : iter_(other.base())
	{}

	template<class Iter2>
	reverse_iterator &operator=(const reverse_iterator<Iter2> &rhs)
	{
		iter_ = rhs.base();
		return (*this);
	}

	~reverse_iterator() {}

	iterator_type base() const
	{
		return (iter_);
	}

	reference operator*() const
	{
		Iter tmp = iter_;
		return (*(--tmp));
	}

	pointer operator->() const
	{
		Iter tmp = iter_;
		return ((--tmp).base());
	}

	reference operator[](difference_type n) const
	{
		return (*(*this + n));
	}

	reverse_iterator &operator+=(difference_type n)
	{
		iter_ -= n;
		return (*this);
	}

	reverse_iterator operator+(difference_type n) const
	{
		return (reverse_iterator(iter_ - n));
	}

	reverse_iterator &operator++()
	{
		--iter_;
		return (*this);
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator tmp(*this);

		--iter_;
		return (tmp);
	}

	reverse_iterator &operator-=(difference_type n)
	{
		iter_ += n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return (reverse_iterator(iter_ + n));
	}

	reverse_iterator &operator--()
	{
		++iter_;
		return (*this);
	}
	reverse_iterator operator--(int)
	{
		reverse_iterator tmp(*this);

		++iter_;
		return (tmp);
	}
};

template<class IterL, class IterR>
bool operator==(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (lhs.base() == rhs.base());
}

template<class IterL, class IterR>
bool operator!=(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (!(lhs == rhs));
}

template<class IterL, class IterR>
bool operator<(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (lhs.base() > rhs.base());
}

template<class IterL, class IterR>
bool operator<=(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (!(rhs < lhs));
}

template<class IterL, class IterR>
bool operator>(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (rhs < lhs);
}

template<class IterL, class IterR>
bool operator>=(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (!(lhs < rhs));
}

template<class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &rev_it)
{
	return (reverse_iterator<Iter>(rev_it + n));
}

template<class IterL, class IterR>
typename reverse_iterator<IterL>::difference_type
operator-(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs)
{
	return (rhs.base() - lhs.base());
}

} // namespace ft

#endif // !REVERSE_ITERATOR_HPP
