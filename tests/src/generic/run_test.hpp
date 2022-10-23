#pragma once

#include "construction_test.hpp"
#include "capacity_test.hpp"
#include "iterator_test.hpp"

namespace generic
{
	static const std::string file_name_prefix = "generic_";
	static const std::string file_name_postfix = FILE_NAME_POSTFIX;

	template < class TestCase >
	static void run_test(const std::string &test_case_name)
	{
		static const std::string file_name = file_name_prefix + test_case_name + file_name_postfix;
		std::ofstream ofs(file_name.c_str());
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