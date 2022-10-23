
#include "tests.hpp"
#include "generic/test.hpp"

int main()
{
	generic::construction::run_test<NAMESPACE::vector<TYPE> >();
	generic::construction::run_test<NAMESPACE::map<TYPE, TYPE> >();
	generic::construction::run_test<NAMESPACE::set<TYPE> >();
}