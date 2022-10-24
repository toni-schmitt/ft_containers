#pragma once

#include <string>
#include <ostream>
#include <fstream>
#include "tests/out_file_stream.hpp"
#include <exception>

namespace tester
{
	static const std::string file_name_prefix = "/tmp/";

	/**
	 * Runs a single Test
	 * @tparam TestCase Class (based on i_base_test)
	 * @param test_case_name Name of the Test Case
	 * @return Path to logfile of test
	 * @details Constructs 'TestCase' and runs tests
	 */
	template < class TestCase >
	static std::string run_test(const std::string &test_case_name)
	{
		std::string test_file_name = file_name_prefix + test_case_name;
		out_file_stream ofs(test_file_name, std::ofstream::out);
		try
		{
			TestCase test_case(false);
			test_case.test(&ofs);
		}
		catch (std::exception &e)
		{
			ofs << "Failure, Exception: " << e.what() << std::endl;
			ofs.close();
			return test_file_name;
		}
		catch (...)
		{
			ofs << "Failure, Unknown Exception" << std::endl;
			ofs.close();
			return test_file_name;
		}
		ofs << "Success" << std::endl;
		ofs.close();
		return test_file_name;
	}
}
