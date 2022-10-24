#pragma once

#include <fstream>

template < class Container >
class i_base_test
{
protected:
	typedef Container container_type;
	typedef typename container_type::value_type value_type;

	std::ofstream &ofs;
	std::string test_name;
	container_type container;

	explicit i_base_test(std::ofstream &ofs, const std::string &test_name) : ofs(ofs), test_name(test_name) { }

	virtual void test() = 0;

	void print_test_start()
	{
		this->ofs << "Running Tests for " << test_name << " (Generic Container)" << std::endl;
	}

	void print_test_end()
	{
		this->ofs << "Done with Tests for " << test_name << " (Generic Container)" << std::endl;
	}
};