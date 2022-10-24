#pragma once

#include <string>
#include <ostream>
#include <fstream>
#include <exception>

namespace tester
{
	static const std::string file_name_prefix = "/tmp/generic_";
	std::string test_file_name = "nan";

	template < class TestCase >
	static std::string run_test(const std::string &test_case_name)
	{
		test_file_name = file_name_prefix + test_case_name;
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
			return test_file_name;
		}
		ofs << "Success" << std::endl;
		ofs.close();
		return test_file_name;
	}
}
