#pragma once

#include "../i_base_test.hpp"
#include "../utility/write.hpp"
#include "../utility/test_cases.hpp"

namespace vector
{
	namespace element_access
	{
		template < class Container >
		class element_access : public i_base_test<Container>
		{
			typedef typename i_base_test<Container>::container_type container_type;
			typedef typename i_base_test<Container>::value_type value_type;

			void test()
			{
				this->print_test_start();

				this->container = container_type();

				this->ofs << "Testing with empty Container:" << std::endl;
//				_test_operator(this->container); // undefined behaviour
				this->_test_at(this->container);
//				_test_front(this->container); // undefined behaviour
//				_test_back(this->container); // undefined behaviour

				value_type *test_case = test_cases::get_test_case(value_type());
				container_type range = container_type(test_case, test_case + test_cases::size);
				this->ofs << "Testing with Container of Size " << range.size() << std::endl;
				this->_test_operator(range);
				this->_test_at(range);
				this->_test_front(range);
				this->_test_back(range);

				this->print_test_end();
			}

		private:
			void _test_operator(container_type &container)
			{
				this->ofs << "operator[]" << std::endl;
				for (size_t i = 0; i < 100; ++i)
				{
					this->ofs << container[ i ] << ',';
				}
				this->ofs << std::endl;
			}

			void _test_at(container_type &container)
			{
				this->ofs << "at()" << std::endl;
				for (typename container_type::size_type i = -100; i < 100; ++i)
				{
					try
					{
						this->ofs << container.at(i) << ',';
					}
					catch (std::exception &e)
					{
						this->ofs << e.what() << ',';
					}
				}
				this->ofs << std::endl;
			}

			void _test_front(container_type container)
			{
				this->ofs << "front()" << std::endl;

				while (container.size() > 10)
				{
					this->ofs << container.front() << std::endl;
					write::iterator::to_file(container.begin(), container.end(), this->ofs);
					container.resize(container.size() - 10);
				}

				this->ofs << std::endl;
			}

			void _test_back(container_type &container)
			{
				this->ofs << "front()" << std::endl;

				while (container.size() > 10)
				{
					this->ofs << container.back() << std::endl;
					write::iterator::to_file(container.end(), container.end(), this->ofs);
					container.resize(container.size() - 10);
				}

				this->ofs << std::endl;
			}

		public:
			explicit element_access(
					std::ofstream &ofs,
					bool run_test_in_constructor = true
			) : i_base_test<Container>(ofs, "VectorElementAccess")
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