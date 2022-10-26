#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace set
{
	template < class Container >
	struct operations_test : public i_base_test<Container>
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

			this->_test_find(this->container);
			this->_test_count(this->container);
			this->_test_lower_bound(this->container);
			this->_test_upper_bound(this->container);
			this->_test_equal_range(this->container);


			this->print_test_end();
		}

	private:
		void _test_find(container_type &container)
		{
			(*this->ofs) << "find()" << std::endl;

			value_type *test_case = GET_TEST_CASE;

			for (size_t i = 0; i < 20 && i < container.size(); ++i)
			{
				TRY_CATCH_WRITE(
						(*this->ofs) << *container.find(test_case[ i ]) << ','
				)
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

		void _test_count(container_type &container)
		{
			(*this->ofs) << "count()" << std::endl;

			value_type *test_case = GET_TEST_CASE;

			for (size_t i = 0; i < 20 && i < container.size(); ++i)
			{
				TRY_CATCH_WRITE(
						(*this->ofs) << container.count(test_case[ i ]) << ','
				)
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

		void _test_lower_bound(container_type &container)
		{
			(*this->ofs) << "lower_bound()" << std::endl;

			value_type *test_case = GET_TEST_CASE;

			for (size_t i = 0; i < 20 && i < container.size(); ++i)
			{
				TRY_CATCH_WRITE(
						(*this->ofs) << *container.lower_bound(test_case[ i ]) << ','
				)
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

		void _test_upper_bound(container_type &container)
		{
			(*this->ofs) << "upper_bound()" << std::endl;

			value_type *test_case = GET_TEST_CASE;

			for (size_t i = 0; i < 20 && i < container.size(); ++i)
			{
				TRY_CATCH_WRITE(
						(*this->ofs) << *container.upper_bound(test_case[ i ]) << ','
				)
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

		void _test_equal_range(container_type &container)
		{
			(*this->ofs) << "equal_range()" << std::endl;

			value_type *test_case = GET_TEST_CASE;

			for (size_t i = 0; i < 20 && i < container.size(); ++i)
			{

				TRY_CATCH_WRITE(
						(*this->ofs) << *container.equal_range(test_case[ i ]).first << ':'
									 << *container.equal_range(test_case[ i ]).second << ','
				)
			}
			(*this->ofs) << std::endl;

			(*this->ofs) << std::endl;
		}

	public:
		explicit operations_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("SetOperations")
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