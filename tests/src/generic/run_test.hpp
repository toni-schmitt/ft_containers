#pragma once

#include "construction_test.hpp"
#include "capacity_test.hpp"
#include "iterator_test.hpp"

namespace generic
{
	static const std::string file_name_prefix = "/tmp/generic_";
	std::string file_name_postfix;
	std::string test_file_name = "nan";

	template < class TestCase >
	static void run_test(const std::string &test_case_name)
	{
		test_file_name = file_name_prefix + test_case_name + file_name_postfix;
		std::ofstream ofs(test_file_name.c_str());
		try
		{
			TestCase(ofs, true);
		}
		catch (std::exception &e)
		{
			ofs << "Failure, Exception: " << e.what() << std::endl;
			ofs.close();
		}
		catch (...)
		{
			ofs << "Failure, Unknown Exception" << std::endl;
			ofs.close();
		}
		ofs << "Success" << std::endl;
		ofs.close();
	}
}