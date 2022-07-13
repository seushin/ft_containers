#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator/iterator.hpp"
#include "iterator/iterator_traits.hpp"

namespace ft
{
template<class Iter>
class random_access_iterator : public iterator<random_access_iterator_tag,
										typename iterator_traits<Iter>::value_type,
										typename iterator_traits<Iter>::difference_type,
										typename iterator_traits<Iter>::reference>
{
private:
	Iter curr_;

	typedef iterator<random_access_iterator_tag,
					 typename iterator_traits<Iter>::value_type,
					 typename iterator_traits<Iter>::difference_type,
					 typename iterator_traits<Iter>::reference>
			base_iterator;

public:
	// clang-format off
	typedef typename base_iterator::iterator_category iterator_category;
	typedef typename base_iterator::difference_type   value_type;
	typedef typename base_iterator::difference_type   difference_type;
	typedef typename base_iterator::reference         reference;
	typedef typename base_iterator::pointer           pointer;
	// clang-format on

	random_access_iterator() : curr_(Iter()) {}

	random_access_iterator(const Iter &iter) : curr_(iter) {}

	random_access_iterator(const random_access_iterator &other) : curr_(other.curr_) {}

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
	random_access_iterator operator+(const difference_type &n)
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
	random_access_iterator operator-(const difference_type &n)
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

template<class Iter>
random_access_iterator<Iter> operator+(const typename random_access_iterator<Iter>::difference_type n,
								random_access_iterator<Iter> it)
{
	return (random_access_iterator<Iter>(it + n));
}

} // namespace ft

#endif // !VECTOR_ITERATOR_HPP
