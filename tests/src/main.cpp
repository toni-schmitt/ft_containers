
#include "tests.hpp"
#include "generic/run_test.hpp"

int main()
{
	generic::run_test<generic::construction::construction_test<NAMESPACE::vector<TYPE> > >("construction_test");

}