#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace map
{
	template < class Container >
	struct element_access_test : public i_base_test<Container>
	{
		typedef typename i_base_test<Container>::container_type container_type;
		typedef typename i_base_test<Container>::value_type value_type;

		void test(out_file_stream *ofs = NULL)
		{
			if (ofs != NULL)
			{
				this->update_ofs(ofs);
			}

			this->print_test_start();

			this->container = FILL_CONTAINER_WITH_TEST_CASE;
			(*this->ofs) << "Testing with Container of Size " << this->container.size() << std::endl;

			this->_test_operator(this->container);
			this->_test_at(this->container);

			this->print_test_end();
		}

	private:
		void _test_operator(container_type &container)
		{
			(*this->ofs) << "operator[]" << std::endl;

			value_type *test_case = GET_TEST_CASE;
			std::srand(test_case[ 0 ].first);

			for (size_t i = 0; i < container.size() / 2 && i < test_cases::size; ++i)
			{
				size_t index;
				do
				{
					index = std::rand() % 10;
				} while (index >= container.size());
				TRY_CATCH_WRITE((*this->ofs) << container[ index ] << ',');
				TRY_CATCH_WRITE((*this->ofs) << (container[ index ] = test_case[ i ].first) << ',');
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

		void _test_at(container_type &container)
		{
			(*this->ofs) << "at()" << std::endl;

			value_type *test_case = GET_TEST_CASE;
			std::srand(test_case[ 0 ].first);

			for (size_t i = 0; i < container.size() / 2; ++i)
			{
				TRY_CATCH_WRITE((*this->ofs) << container.at(std::rand() % 10) << ',');
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

	public:
		explicit element_access_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("MapElementAccess")
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