#pragma once

#include "construction_test.hpp"
#include "capacity_test.hpp"

namespace generic
{
	static const std::string file_name_prefix = "generic_";
	static const std::string file_name_postfix = FILE_NAME_POSTFIX;

	namespace construction
	{
		template < class Container >
		static void run_test()
		{
			static const std::string file_name = file_name_prefix + "construction_test" + file_name_postfix;
			std::ofstream ofs(file_name.c_str());
			try
			{
				construction_test<Container>(ofs, true);
			}
			catch (...)
			{
				ofs << "Failure" << std::endl;
				ofs.close();
			}
			ofs << "Success" << std::endl;
			ofs.close();
		}
	}

	namespace capacity
	{
		template < class Container >
		static void run_test()
		{
			static const std::string file_name = file_name_prefix + "capacity_test" + file_name_postfix;
			std::ofstream ofs(file_name.c_str());
			try
			{
				capacity_test<Container>(ofs, true);
			}
			catch (...)
			{
				ofs << "Failure" << std::endl;
				ofs.close();
			}
			ofs << "Success" << std::endl;
			ofs.close();
		}
	}
}