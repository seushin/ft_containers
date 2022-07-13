#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <cstdint>

namespace ft
{

template<bool is_integral, class T>
struct is_integral_base
{
	typedef T type;
	static const bool value = is_integral;
};

template<class T>
struct is_integral : public is_integral_base<false, T>
{};

template<>
struct is_integral<bool> : public is_integral_base<true, bool>
{};

template<>
struct is_integral<char> : public is_integral_base<true, char>
{};

template<>
struct is_integral<char16_t> : public is_integral_base<true, char16_t>
{};

template<>
struct is_integral<char32_t> : public is_integral_base<true, char32_t>
{};

template<>
struct is_integral<wchar_t> : public is_integral_base<true, wchar_t>
{};

template<>
struct is_integral<signed char> : public is_integral_base<true, signed char>
{};

template<>
struct is_integral<short int> : public is_integral_base<true, short int>
{};

template<>
struct is_integral<int> : public is_integral_base<true, int>
{};

template<>
struct is_integral<long int> : public is_integral_base<true, long int>
{};

template<>
struct is_integral<long long int> : public is_integral_base<true, long long int>
{};

template<>
struct is_integral<unsigned char> : public is_integral_base<true, unsigned char>
{};

template<>
struct is_integral<unsigned short int> : public is_integral_base<true, unsigned short int>
{};

template<>
struct is_integral<unsigned int> : public is_integral_base<true, unsigned int>
{};

template<>
struct is_integral<unsigned long int> : public is_integral_base<true, unsigned long int>
{};

template<>
struct is_integral<unsigned long long int> : public is_integral_base<true, unsigned long long int>
{};

} // namespace ft

#endif // !IS_INTEGRAL_HPP
