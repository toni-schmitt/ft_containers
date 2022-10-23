
#include "tests.hpp"
#include "generic/run_test.hpp"

#include <fstream>
#include <iterator>
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

template < class Container >
static void run_generic_tests()
{
	generic::run_test<generic::construction::construction_test<Container> >("construction");
	generic::run_test<generic::capacity::capacity_test<Container> >("capacity");
	generic::run_test<generic::iterator::iterator_test<Container> >("iterator");
}

template < class ContainerSTD, class ContainerFT >
static bool run_generic_construction_test()
{
	static const std::string test_case_name = "construction";

	std::string std_log;
	std::string ft_log;

	generic::file_name_postfix = "std.log";
	generic::run_test<generic::construction::construction_test<ContainerSTD> >(test_case_name);
	std_log = generic::test_file_name;
	generic::file_name_postfix = "ft.log";
	generic::run_test<generic::construction::construction_test<ContainerFT> >(test_case_name);
	ft_log = generic::test_file_name;
	return compare_files(std_log, ft_log);
}

template < class ContainerSTD, class ContainerFT >
static bool run_generic_capacity_test()
{
	static const std::string test_case_name = "capacity";

	std::string std_log;
	std::string ft_log;

	generic::file_name_postfix = "std.log";
	generic::run_test<generic::capacity::capacity_test<ContainerSTD> >(test_case_name);
	std_log = generic::test_file_name;
	generic::file_name_postfix = "ft.log";
	generic::run_test<generic::capacity::capacity_test<ContainerFT> >(test_case_name);
	ft_log = generic::test_file_name;
	return compare_files(std_log, ft_log);
}

template < class ContainerSTD, class ContainerFT >
static bool run_generic_iterator_test()
{
	static const std::string test_case_name = "iterator";

	std::string std_log;
	std::string ft_log;

	generic::file_name_postfix = "std.log";
	generic::run_test<generic::iterator::iterator_test<ContainerSTD> >(test_case_name);
	std_log = generic::test_file_name;
	generic::file_name_postfix = "ft.log";
	generic::run_test<generic::iterator::iterator_test<ContainerFT> >(test_case_name);
	ft_log = generic::test_file_name;
	return compare_files(std_log, ft_log);
}


static void run_generic_tests()
{
	typedef ft_namespace::namespace_chooser ft_chooser;
	typedef std_namespace::namespace_chooser std_chooser;

	std::cout << "Running Generic Construction Test:" << std::endl;
	std::cout << "Success: " << std::boolalpha
			  << run_generic_construction_test<std_chooser::vector, ft_chooser::vector>()
			  << std::endl;
	std::cout << "Running Generic Capacity Test:" << std::endl;
	std::cout << "Success: " << std::boolalpha << run_generic_capacity_test<std_chooser::vector, ft_chooser::vector>()
			  << std::endl;
	std::cout << "Running Generic Iterator Test:" << std::endl;
	std::cout << "Success: " << std::boolalpha << run_generic_iterator_test<std_chooser::vector, ft_chooser::vector>()
			  << std::endl;
}

int main()
{
	run_generic_tests();
}