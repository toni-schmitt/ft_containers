#pragma once

#include "i_generic.hpp"
#include "../test_cases.hpp"
#include "../write.hpp"

namespace generic
{
	namespace iterator
	{
		template < class Container >
		class iterator_test : public i_generic<Container>
		{
			typedef typename i_generic<Container>::container_type container_type;
			typedef typename i_generic<Container>::value_type value_type;

			void test()
			{
				this->print_test_start();

				value_type *test_case = test_cases::get_test_case(value_type());
				container_type range = container_type(test_case, test_case + test_cases::size);

				// Begin
				this->ofs << "Testing \'.begin()\' on empty Container" << std::endl;
				this->ofs << *this->container.begin() << std::endl;
				this->ofs << "Testing \'.begin()\' on Container with a size of " << range.size() << std::endl;
				this->ofs << *range.begin() << std::endl;

				// End
				this->ofs << "Testing \'.end()\' on empty Container" << std::endl;
				this->ofs << *this->container.end() << std::endl;
				this->ofs << "Testing \'.end()\' on Container with a size of " << range.size() << std::endl;
				this->ofs << *range.end() << std::endl;

				// RBegin
				this->ofs << "Testing \'.rbegin()\' on empty Container" << std::endl;
				this->ofs << *this->container.rbegin() << std::endl;
				this->ofs << "Testing \'.rbegin()\' on Container with a size of " << range.size() << std::endl;
				this->ofs << *range.rbegin() << std::endl;

				// REnd
				this->ofs << "Testing \'.rend()\' on empty Container" << std::endl;
				this->ofs << *this->container.rend() << std::endl;
				this->ofs << "Testing \'.rend()\' on Container with a size of " << range.size() << std::endl;
				this->ofs << *range.rend() << std::endl;

				try
				{
					// Incrementing
					this->ofs << "Testing \'.operator++()\' on empty Container" << std::endl;
					this->ofs << "\'.begin()\'" << std::endl;
					this->ofs << *(this->container.begin().operator++()) << std::endl;
					this->ofs << "\'.end()\'" << std::endl;
					this->ofs << *(this->container.end().operator++()) << std::endl;
					this->ofs << "\'.rbegin()\'" << std::endl;
					this->ofs << *(this->container.rbegin().operator++()) << std::endl;
					this->ofs << "\'.rend()\'" << std::endl;
					this->ofs << *(this->container.rend().operator++()) << std::endl;

					this->ofs << "Testing \'.operator++()\' on Container with a size of " << range.size() << std::endl;
					this->ofs << "\'.begin()\'" << std::endl;
					this->ofs << *(range.begin().operator++()) << std::endl;
					this->ofs << "\'.end()\'" << std::endl;
					this->ofs << *(range.end().operator++()) << std::endl;
					this->ofs << "\'.rbegin()\'" << std::endl;
					this->ofs << *(range.rbegin().operator++()) << std::endl;
					this->ofs << "\'.rend()\'" << std::endl;
					this->ofs << *(range.rend().operator++()) << std::endl;

					// Decrementing
					this->ofs << "Testing \'.operator--()\' on empty Container" << std::endl;
					this->ofs << "\'.begin()\'" << std::endl;
					this->ofs << *(this->container.begin().operator--()) << std::endl;
					this->ofs << "\'.end()\'" << std::endl;
					this->ofs << *(this->container.end().operator--()) << std::endl;
					this->ofs << "\'.rbegin()\'" << std::endl;
					this->ofs << *(this->container.rbegin().operator--()) << std::endl;
					this->ofs << "\'.rend()\'" << std::endl;
					this->ofs << *(this->container.rend().operator--()) << std::endl;

					this->ofs << "Testing \'.operator--()\' on Container with a size of " << range.size() << std::endl;
					this->ofs << "\'.begin()\'" << std::endl;
					this->ofs << *(range.begin().operator--()) << std::endl;
					this->ofs << "\'.end()\'" << std::endl;
					this->ofs << *(range.end().operator--()) << std::endl;
					this->ofs << "\'.rbegin()\'" << std::endl;
					this->ofs << *(range.rbegin().operator--()) << std::endl;
					this->ofs << "\'.rend()\'" << std::endl;
					this->ofs << *(range.rend().operator--()) << std::endl;
				}
				catch (std::exception &e)
				{
					this->ofs << "Exception: " << e.what() << std::endl;
				}
				catch (...)
				{
					this->ofs << "Exception of unknown type was thrown" << std::endl;
				}

				this->print_test_end();
			}

		public:
			explicit iterator_test(
					std::ofstream &ofs,
					bool run_test_in_constructor = true
			) : i_generic<Container>(ofs, "iterator_test")
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