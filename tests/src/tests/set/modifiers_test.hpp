#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace set
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

			this->container = FILL_CONTAINER_WITH_TEST_CASE;

			this->_test_insert(this->container);

			this->_test_erase(this->container);

			this->_test_insert(this->container);

			this->_test_swap(this->container);

			this->_test_clear(this->container);

			this->print_test_end();
		}

	private:
		void _test_insert(container_type &container)
		{
			(*this->ofs) << "insert()" << std::endl;
			write::container::to_file(container, *this->ofs);
			value_type *test_case = GET_TEST_CASE;

			typedef typename container_type::iterator iterator;

			(*this->ofs) << "single element (1)" << std::endl;
			for (size_t i = 0; i < container.size() / 4; ++i)
			{
				TRY_CATCH_WRITE(
						container.insert(test_case[ i ])
				);
			}
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "with hint (2)" << std::endl;
			for (size_t i = 0; i < container.size() / 4; ++i)
			{
				iterator result;
				TRY_CATCH_WRITE(result = container.insert(container.begin(), test_case[ i ]));
				(*this->ofs) << *result << ',';
			}
			(*this->ofs) << std::endl;
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "range (3)" << std::endl;
			for (size_t i = 0; i < container.size() / 4; ++i)
			{
				TRY_CATCH_WRITE(
						container.insert(test_case, test_case + (test_cases::size / 2))
				);
			}

			write::container::to_file(container, *this->ofs);
			(*this->ofs) << std::endl;
		}

		void _test_erase(container_type &container)
		{

			(*this->ofs) << "erase()" << std::endl;
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "position (1)" << std::endl;
			for (size_t i = 0; i < container.size() / 10; ++i)
			{
				TRY_CATCH_WRITE(container.erase(container.begin()))
			}
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "key (2)" << std::endl;
			value_type *test_case = GET_TEST_CASE;
			for (size_t i = 0; i < container.size() / 10; ++i)
			{
				TRY_CATCH_WRITE((*this->ofs) << container.erase(test_case[ i ]) << ',');
			}
			write::container::to_file(container, *this->ofs);
			(*this->ofs) << std::endl;

			(*this->ofs) << "range (3)" << std::endl;
			typename container_type::iterator pos = container.insert(container.begin(), test_case[ 0 ]);
			TRY_CATCH_WRITE(container.erase(container.begin(), pos));
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << std::endl;
		}

		void _test_swap(container_type &container)
		{
			(*this->ofs) << "swap()" << std::endl;

			container_type filled_container = FILL_CONTAINER_WITH_TEST_CASE;
			write::container::to_file(filled_container, *this->ofs);
			write::container::to_file(container, *this->ofs);
			container.swap(filled_container);
			write::container::to_file(filled_container, *this->ofs);
			write::container::to_file(container, *this->ofs);

			this->_test_clear(filled_container);

			(*this->ofs) << std::endl;
		}

		void _test_clear(container_type &container)
		{
			(*this->ofs) << "clear()" << std::endl;

			write::container::to_file(container, *this->ofs);
			container.clear();
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << std::endl;
		}

	public:
		explicit modifiers_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("SetModifiers")
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