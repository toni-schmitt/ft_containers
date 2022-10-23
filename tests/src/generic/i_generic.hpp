#pragma once

#include <fstream>

namespace generic
{
	template < class Container >
	class i_generic
	{
	protected:
		typedef Container container_type;
		typedef typename container_type::value_type value_type;

		std::ofstream &ofs;
		std::string test_name;
		container_type container;

		explicit i_generic(std::ofstream &ofs, std::string test_name) : ofs(ofs), test_name(test_name) { }

		virtual void test() = 0;

		void print_test_start()
		{
			this->ofs << "Running Tests for " << test_name << " (Generic Container)" << std::endl;
		}

		void print_test_end()
		{
			this->ofs << "Done with Tests for " << test_name << " (Generic Container)" << std::endl;
		}
	};
}