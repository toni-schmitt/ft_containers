#pragma once

#include "../i_base_test.hpp"
#include "../utility/write.hpp"
#include "../utility/test_cases.hpp"
#include <fstream>

namespace generic
{
	namespace construction
	{
		template < class Container >
		class construction_test : public i_base_test<Container>
		{
			typedef typename i_base_test<Container>::container_type container_type;
			typedef typename i_base_test<Container>::value_type value_type;

			void test()
			{
				this->print_test_start();

				// Default Constructor
				this->ofs << "Calling Default Constructor" << std::endl;
				this->container = container_type();
				write::container::to_file(this->container, this->ofs);

				// Range Constructor
				this->ofs << "Calling Range Constructor" << std::endl;
				value_type *test_case = test_cases::get_test_case(value_type());
				container_type range = container_type(test_case, test_case + test_cases::size);
				write::container::to_file(range, this->ofs);

				// Copy Constructor
				this->ofs << "Calling Copy Constructor" << std::endl;
				container_type copy = container_type(range);
				write::container::to_file(copy, this->ofs);
				write::container::to_file(range, this->ofs);
				copy = this->container;
				write::container::to_file(copy, this->ofs);
				write::container::to_file(range, this->ofs);


				this->ofs << "Testing Destruction" << std::endl;
				{
					container_type tmp = container_type(range);
					write::container::to_file(tmp, this->ofs);
				}

				this->print_test_end();
			}

		public:
			explicit construction_test(
					std::ofstream &ofs,
					bool run_test_in_constructor = true
			) : i_base_test<Container>(ofs, "Construction")
			{
				if (!run_test_in_constructor)
					return;

				try
				{
					this->test();
				}
				catch (...)
				{
					throw;
				}
			}
		};
	}
}