#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace stack
{
	template < class Container >
	struct capacity_test : public i_base_test<Container>
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

			{
				container_type empty_container;
				this->_test_empty(empty_container);
				this->_test_size(empty_container);
			}

			{
				typedef typename container_type::container_type underlying_container;
				value_type *test_case = GET_TEST_CASE;
				underlying_container cntr = underlying_container(test_case, test_case + test_cases::size);
				this->container = container_type(cntr);
			}
			this->_test_empty(this->container);
			this->_test_size(this->container);

			this->print_test_end();
		}

	private:
		void _test_empty(container_type &container)
		{
			(*this->ofs) << ".empty()" << std::endl;

			TRY_CATCH_WRITE((*this->ofs) << container.empty() << std::endl);

			(*this->ofs) << std::endl;
		}

		void _test_size(container_type &container)
		{
			(*this->ofs) << ".size()" << std::endl;

			TRY_CATCH_WRITE((*this->ofs) << container.size() << std::endl);

			(*this->ofs) << std::endl;
		}

	public:
		explicit capacity_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("StackCapacity")
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