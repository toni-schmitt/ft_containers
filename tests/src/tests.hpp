#pragma once

#include <fstream>
#include <ostream>

#if !defined(TYPE)
#error "Must specify a Type for the Containers"
#endif


// Includes ft/std Containers

#include <vector>
#include <map>
#include <set>
#include <stack>

#undef STD

#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"


template < class T1, class T2 >
std::ostream &operator<<(std::ostream &os, ft::pair<T1, T2> pair)
{
	os << pair.first << ':' << pair.second;
	return os;
}

template < class T1, class T2 >
std::ofstream &operator<<(std::ofstream &ofs, ft::pair<T1, T2> pair)
{
	ofs << pair.first << ':' << pair.second;
	return ofs;
}

template < class T1, class T2 >
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> pair)
{
	os << pair.first << ':' << pair.second;
	return os;
}

template < class T1, class T2 >
std::ofstream &operator<<(std::ofstream &ofs, std::pair<T1, T2> pair)
{
	ofs << pair.first << ':' << pair.second;
	return ofs;
}


namespace std_namespace
{
	struct namespace_chooser
	{
		typedef std::vector<TYPE> vector;
		typedef std::map<TYPE, TYPE> map;
		typedef std::set<TYPE> set;
		typedef std::stack<TYPE> stack;
		typedef std::pair<TYPE, TYPE> pair;
	};
}

namespace ft_namespace
{
	struct namespace_chooser
	{
		typedef ft::vector<TYPE> vector;
		typedef ft::map<TYPE, TYPE> map;
		typedef ft::set<TYPE> set;
		typedef ft::stack<TYPE> stack;
		typedef ft::pair<TYPE, TYPE> pair;
	};
}
