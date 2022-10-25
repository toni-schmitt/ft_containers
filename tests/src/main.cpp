
#include "utility/tests.hpp"
#include "run_test.hpp"
#include "tests/generic/construction_test.hpp"
#include "tests/generic/iterator_test.hpp"
#include "tests/generic/capacity_test.hpp"

#include <ostream>


int main(int argc, char *argv[])
{
	switch (argc)
	{
		case 1: // Run all Tests
			break;
		case 2: // Run single Container / Run single Test (for all Containers)
			break;
		case 3: // Run single Test for Container
			break;
		default:
			std::cerr << argv[ 0 ] << " cannot have more than 3 Arguments" << std::endl;
			return EXIT_FAILURE;
	}

	tester::test::run("vector", "all");
//	tester::test::run("map", "all");
//	tester::test::run("set", "all");
//	tester::test::run("stack", "all");
//	run_generic_tests();
}