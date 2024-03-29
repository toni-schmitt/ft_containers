#pragma once

namespace ft
{
	template < bool B, typename T = void >
	struct enable_if
	{
	};

	template < typename T >
	struct enable_if<true, T>
	{
		typedef T type;
	};

	struct true_type
	{
		static const bool value = true;
		typedef true_type type;
	};

	struct false_type
	{
		static const bool value = false;
		typedef false_type type;
	};

	template < typename T >
	struct remove_const
	{
		typedef T type;
	};

	template < typename T >
	struct remove_const<const T>
	{
		typedef T type;
	};

	template < typename T >
	struct remove_volatile
	{
		typedef T type;
	};

	template < typename T >
	struct remove_volatile<volatile T>
	{
		typedef T type;
	};

	template < typename T >
	struct remove_cv
	{
		typedef typename remove_volatile<typename remove_const<T>::type>::type type;
	};

	template < typename >
	struct is_integral_base : public false_type { };

	template < >
	struct is_integral_base<bool> : public true_type { };

	template < >
	struct is_integral_base<char> : public true_type { };

	template < >
	struct is_integral_base<signed char> : public true_type { };

	template < >
	struct is_integral_base<short int> : public true_type { };

	template < >
	struct is_integral_base<int> : public true_type { };

	template < >
	struct is_integral_base<long int> : public true_type { };

	template < >
	struct is_integral_base<unsigned char> : public true_type { };

	template < >
	struct is_integral_base<unsigned short int> : public true_type { };

	template < >
	struct is_integral_base<unsigned int> : public true_type { };

	template < >
	struct is_integral_base<unsigned long int> : public true_type { };

	template < typename T >
	struct is_integral : is_integral_base<typename remove_cv<T>::type> { };

	template < typename T, typename U >
	struct is_same : public false_type { };

	template < typename T >
	struct is_same<T, T> : public true_type { };
} // namespace ft
