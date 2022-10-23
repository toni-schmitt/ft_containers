#pragma once


// Defines ft/std Namespace (and file postfix)
#if defined(STD) && STD == 1

#define FILE_NAME_POSTFIX "_std.log"
#define NAMESPACE std

#elif defined(FT) && FT == 1

#define NAMESPACE ft
#define FILE_NAME_POSTFIX "_ft.log"

#else
#error "No Namespace Defined"
#endif

#include <fstream>
#include <ostream>

#if !defined(TYPE)
#error "Must specify a Type for the Containers"
#endif


// Includes ft/std Containers
#if defined(STD) && STD == 1

#include <vector>
#include <map>
#include <set>
#include <stack>

#undef STD

#elif defined(FT) && FT == 1

#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"

#undef FT

#else
#error "No Namespace Defined"
#endif

template < class T1, class T2 >
std::ostream &operator<<(std::ostream &os, NAMESPACE::pair<T1, T2> pair)
{
	os << pair.first << ':' << pair.second;
	return os;
}

template < class T1, class T2 >
std::ofstream &operator<<(std::ofstream &ofs, NAMESPACE::pair<T1, T2> pair)
{
	ofs << pair.first << ':' << pair.second;
	return ofs;
}