
#include "utility/tests.hpp"
#include "run_test.hpp"
#include "tests/generic/construction_test.hpp"
#include "tests/generic/iterator_test.hpp"
#include "tests/generic/capacity_test.hpp"

#include <ostream>

template < class ContainerSTD, class ContainerFT >
static bool run_generic_construction_test()
{
	static const std::string test_case_name = "construction";

	std::string std_log = tester::run_test<generic::construction::construction_test<ContainerSTD> >(
			test_case_name + "std.log");
	std::string ft_log = tester::run_test<generic::construction::construction_test<ContainerFT> >(
			test_case_name + "ft.log");
	return compare_files(std_log, ft_log);
}

template < class ContainerSTD, class ContainerFT >
static bool run_generic_capacity_test()
{
	static const std::string test_case_name = "capacity";

	std::string std_log = tester::run_test<generic::capacity::capacity_test<ContainerSTD> >(test_case_name + "std.log");
	std::string ft_log = tester::run_test<generic::capacity::capacity_test<ContainerFT> >(test_case_name + "ft.log");
	return compare_files(std_log, ft_log);
}

template < class ContainerSTD, class ContainerFT >
static bool run_generic_iterator_test()
{
	static const std::string test_case_name = "iterator";

	std::string std_log = tester::run_test<generic::iterator::iterator_test<ContainerSTD> >(test_case_name + "std.log");
	std::string ft_log = tester::run_test<generic::iterator::iterator_test<ContainerFT> >(test_case_name + "ft.log");
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