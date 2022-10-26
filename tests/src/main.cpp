/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:38:17 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:42:03 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utility/tests.hpp"
#include "run_test.hpp"

#include <ostream>


int main(int argc, char *argv[])
{
	system("rm -rf ./logs; rm -rf ./diffs; mkdir ./logs");
	atexit(delete_test_objects);
	switch (argc)
	{
		case 1: // Run all Tests
			tester::test::run("vector", "all");
			tester::test::run("map", "all");
			tester::test::run("set", "all");
			tester::test::run("stack", "all");
			break;
		case 2: // Run single Container
			tester::test::run(argv[ 1 ], "all");
			break;
		case 3: // Run single Test for Container
			tester::test::run(argv[ 1 ], argv[ 2 ]);
			break;
		default:
			std::cerr << argv[ 0 ] << " cannot have more than 3 Arguments" << std::endl;
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}