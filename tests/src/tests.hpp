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

#include <string>
#include <algorithm>

bool compare_files(const std::string &file_1, const std::string &file_2)
{
	std::ifstream file_stream_1(file_1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream file_stream_2(file_2, std::ifstream::binary | std::ifstream::ate);

	if (file_stream_1.fail() || file_stream_2.fail())
		return false; //file problem

	if (file_stream_1.tellg() != file_stream_2.tellg())
		return false; //size mismatch

	//seek back to beginning and use std::equal to compare contents
	file_stream_1.seekg(0, std::ifstream::beg);
	file_stream_2.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(file_stream_1.rdbuf()),
					  std::istreambuf_iterator<char>(),
					  std::istreambuf_iterator<char>(file_stream_2.rdbuf()));
}