
#include "tests.hpp"
#include "generic/run_test.hpp"

template < class Container >
static void run_generic_tests()
{
	generic::run_test<generic::construction::construction_test<Container> >("construction");
	generic::run_test<generic::capacity::capacity_test<Container> >("capacity");
	generic::run_test<generic::iterator::iterator_test<Container> >("iterator");
}

int main()
{
	run_generic_tests<NAMESPACE::vector<TYPE> >();
}