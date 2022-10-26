#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace stack
{
	template < class Container >
	struct modifiers_test : public i_base_test<Container>
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
				this->_test_push(empty_container);
				this->_test_pop(empty_container);
			}

			{
				typedef typename container_type::container_type underlying_container;
				value_type *test_case = GET_TEST_CASE;
				underlying_container cntr = underlying_container(test_case, test_case + test_cases::size);
				this->container = container_type(cntr);
			}
			this->_test_push(this->container);
			this->_test_pop(this->container);

			this->print_test_end();
		}

	private:
		void _test_push(container_type &container)
		{
			(*this->ofs) << ".push()" << std::endl;
			this->_write_to_file(container);

			value_type *test_case = GET_TEST_CASE;
			std::srand(test_case[ 0 ]);
			const int max = std::rand() % 100;
			for (int i = 0; i < max; ++i)
			{
				TRY_CATCH_WRITE(container.push(test_case[ i ]));
			}

			this->_write_to_file(container);
			(*this->ofs) << std::endl;
		}

		void _test_pop(container_type &container)
		{
			(*this->ofs) << ".pop()" << std::endl;
			this->_write_to_file(container);

			while (!container.empty())
			{
				container.pop();
			}

			this->_write_to_file(container);
			(*this->ofs) << std::endl;
		}

		void _write_to_file(container_type container)
		{
			while (!container.empty())
			{
				(*this->ofs) << container.top() << ',';
				container.pop();
			}
			(*this->ofs) << std::endl;
		}

	public:
		explicit modifiers_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("StackModifiers")
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