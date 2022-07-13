#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator/iterator.hpp"
#include "iterator/iterator_traits.hpp"

namespace ft
{
template<class Iter>
class vector_iterator : public iterator<random_access_iterator_tag,
										typename iterator_traits<Iter>::value_type,
										typename iterator_traits<Iter>::difference_type,
										typename iterator_traits<Iter>::reference>
{
private:
	Iter curr_;

public:
	// clang-format off
	typedef typename iterator_traits<Iter>::iterator_category iterator_category;
	typedef typename iterator_traits<Iter>::difference_type   value_type;
	typedef typename iterator_traits<Iter>::difference_type   difference_type;
	typedef typename iterator_traits<Iter>::reference         reference;
	typedef typename iterator_traits<Iter>::pointer           pointer;
	// clang-format on

	vector_iterator() : curr_(Iter()) {}

	vector_iterator(const Iter &iter) : curr_(iter) {}

	vector_iterator(const vector_iterator &other) : curr_(other.curr_) {}

	vector_iterator &operator=(const vector_iterator &rhs)
	{
		curr_ = rhs.curr_;
	}

	~vector_iterator() {}

	reference operator*() const
	{
		return (*curr_);
	}

	pointer operator->() const
	{
		return (static_cast<pointer>(curr_));
	}

	vector_iterator &operator++()
	{
		++curr_;
		return (*this);
	}
	vector_iterator operator++(int)
	{
		vector_iterator copy(*this);

		++(*this);
		return (copy);
	}

	vector_iterator &operator--()
	{
		--curr_;
		return (*this);
	}
	vector_iterator operator--(int)
	{
		vector_iterator copy(*this);

		--(*this);
		return (copy);
	}

	reference operator[](const difference_type &n)
	{
		return (curr_[n]);
	}

	vector_iterator &operator+=(const difference_type &n)
	{
		curr_ += n;
		return (*this);
	}
	vector_iterator operator+(const difference_type &n)
	{
		vector_iterator it(*this);

		it += n;
		return (it);
	}

	vector_iterator &operator-=(const difference_type &n)
	{
		curr_ -= n;
		return (*this);
	}
	vector_iterator operator-(const difference_type &n)
	{
		vector_iterator it(*this);

		it -= n;
		return (it);
	}

	const Iter &base() const
	{
		return (curr_);
	}
};

template<class IterL, class IterR>
bool operator==(const vector_iterator<IterL> &lhs, const vector_iterator<IterR> &rhs)
{
	return (lhs.base() == rhs.base());
}

template<class IterL, class IterR>
bool operator!=(const vector_iterator<IterL> &lhs, const vector_iterator<IterR> &rhs)
{
	return (!(lhs.base() == rhs.base()));
}

template<class IterL, class IterR>
bool operator<(const vector_iterator<IterL> &lhs, const vector_iterator<IterR> &rhs)
{
	return (lhs.base() < rhs.base());
}

template<class IterL, class IterR>
bool operator<=(const vector_iterator<IterL> &lhs, const vector_iterator<IterR> &rhs)
{
	return (!(rhs < lhs));
}

template<class IterL, class IterR>
bool operator>(const vector_iterator<IterL> &lhs, const vector_iterator<IterR> &rhs)
{
	return (rhs < lhs);
}

template<class IterL, class IterR>
bool operator>=(const vector_iterator<IterL> &lhs, const vector_iterator<IterR> &rhs)
{
	return (!(lhs < rhs));
}

template<class Iter>
vector_iterator<Iter> operator+(const typename vector_iterator<Iter>::difference_type n,
								vector_iterator<Iter> it)
{
	return (vector_iterator<Iter>(it + n));
}

} // namespace ft

#endif // !VECTOR_ITERATOR_HPP
