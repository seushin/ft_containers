#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator/iterator.hpp"
#include "iterator/iterator_traits.hpp"
#include "util/enable_if.hpp"

namespace ft
{

template<class Iter>
class random_access_iterator
{
private:
	Iter curr_;

public:
	// clang-format off
	typedef typename iterator_traits<Iter>::iterator_category iterator_category;
	typedef typename iterator_traits<Iter>::value_type        value_type;
	typedef typename iterator_traits<Iter>::difference_type   difference_type;
	typedef typename iterator_traits<Iter>::reference         reference;
	typedef typename iterator_traits<Iter>::pointer           pointer;
	// clang-format on

	random_access_iterator() : curr_() {}

	random_access_iterator(Iter iter) : curr_(iter) {}

	random_access_iterator(const random_access_iterator &other) : curr_(other.curr_) {}

	template<class Iter2>
	random_access_iterator(
			const random_access_iterator<Iter2> &other,
			typename enable_if<
					is_equal<value_type, typename random_access_iterator<Iter2>::value_type>::value,
					void>::type * = 0)
		: curr_(other.base())
	{}

	random_access_iterator &operator=(const random_access_iterator &rhs)
	{
		curr_ = rhs.curr_;

		return (*this);
	}

	~random_access_iterator() {}

	reference operator*() const
	{
		return (*curr_);
	}

	pointer operator->() const
	{
		return (static_cast<pointer>(curr_));
	}

	random_access_iterator &operator++()
	{
		++curr_;
		return (*this);
	}
	random_access_iterator operator++(int)
	{
		random_access_iterator copy(*this);

		++(*this);
		return (copy);
	}

	random_access_iterator &operator--()
	{
		--curr_;
		return (*this);
	}
	random_access_iterator operator--(int)
	{
		random_access_iterator copy(*this);

		--(*this);
		return (copy);
	}

	reference operator[](const difference_type &n)
	{
		return (curr_[n]);
	}

	random_access_iterator &operator+=(const difference_type &n)
	{
		curr_ += n;
		return (*this);
	}
	random_access_iterator operator+(const difference_type &n) const
	{
		random_access_iterator it(*this);

		it += n;
		return (it);
	}

	random_access_iterator &operator-=(const difference_type &n)
	{
		curr_ -= n;
		return (*this);
	}
	random_access_iterator operator-(const difference_type &n) const
	{
		random_access_iterator it(*this);

		it -= n;
		return (it);
	}

	const Iter &base() const
	{
		return (curr_);
	}
};

template<class IterL, class IterR>
bool operator==(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (lhs.base() == rhs.base());
}

template<class IterL, class IterR>
bool operator!=(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (!(lhs.base() == rhs.base()));
}

template<class IterL, class IterR>
bool operator<(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (lhs.base() < rhs.base());
}

template<class IterL, class IterR>
bool operator<=(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (!(rhs < lhs));
}

template<class IterL, class IterR>
bool operator>(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (rhs < lhs);
}

template<class IterL, class IterR>
bool operator>=(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (!(lhs < rhs));
}

template<class IterL, class IterR>
typename random_access_iterator<IterL>::difference_type
operator-(const random_access_iterator<IterL> &lhs, const random_access_iterator<IterR> &rhs)
{
	return (lhs.base() - rhs.base());
}

template<class Iter>
random_access_iterator<Iter>
operator+(const typename random_access_iterator<Iter>::difference_type n,
		  random_access_iterator<Iter> it)
{
	return (random_access_iterator<Iter>(it + n));
}

} // namespace ft

#endif // !VECTOR_ITERATOR_HPP
