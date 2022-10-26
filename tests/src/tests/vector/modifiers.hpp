/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:40:04 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:40:05 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../utility/test_cases.hpp"
#include "../i_base_test.hpp"
#include "../../utility/write.hpp"

namespace vector
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

			this->container = container_type();

			(*this->ofs) << "Testing with Empty Container: " << std::endl;
			{
				typedef void(modifiers_test<Container>::*tests)(container_type &);
				tests modifiers_tests[] = {
						&modifiers_test<Container>::_test_assign,
						&modifiers_test<Container>::_test_push_back,
						&modifiers_test<Container>::_test_pop_back,
						&modifiers_test<Container>::_test_insert,
//						&modifiers_test<Container>::_test_erase,
						&modifiers_test<Container>::_test_swap,
						&modifiers_test<Container>::_test_clear
				};
				for (int i = 0; i < 6; ++i)
				{
					container_type empty_container;
					(this->*modifiers_tests[ i ])(empty_container);
				}
			}

			(*this->ofs) << "Testing with this->container: " << std::endl;
			this->_test_assign(this->container);
			this->_test_push_back(this->container);
			this->_test_pop_back(this->container);
			this->_test_insert(this->container);
			this->_test_erase(this->container);
			this->_test_swap(this->container);
			this->_test_clear(this->container);


			this->print_test_end();
		}

	private:
		void _test_assign(container_type &container)
		{
			(*this->ofs) << "assign()" << std::endl;
			(*this->ofs) << "container before assign()" << std::endl;
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "range (1)" << std::endl;

			value_type *test_case = test_cases::get_test_case(value_type());
			container_type random_cnt = container_type(test_case, test_case + test_cases::size);

			TRY_CATCH_WRITE(container.assign(random_cnt.begin(), random_cnt.begin() + (random_cnt.size() / 2)));
			write::container::to_file(container, *this->ofs);
			TRY_CATCH_WRITE(container.assign(random_cnt.begin() + (random_cnt.size() / 2), random_cnt.end()));
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "fill (2)" << std::endl;

			TRY_CATCH_WRITE(container.assign(900, test_case[ 0 ]));
			write::container::to_file(container, *this->ofs);
			TRY_CATCH_WRITE(container.assign(2, test_case[ 1 ]));
			write::container::to_file(container, *this->ofs);
			TRY_CATCH_WRITE(container.assign(200000, test_case[ 2 ]));
			write::container::to_file(container, *this->ofs);
			TRY_CATCH_WRITE(container.assign(900000, test_case[ 9 ]));
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << std::endl;
		}

		void _test_push_back(container_type &container)
		{
			(*this->ofs) << "push_back()" << std::endl;

			value_type *test_case = test_cases::get_test_case(value_type());

			write::container::to_file(container, *this->ofs);

			for (int i = 0; i < test_cases::size / 2; ++i)
			{
				TRY_CATCH_WRITE(container.push_back(test_case[ i ]))
			}

			write::container::to_file(container, *this->ofs);

			for (int i = 0; i < test_cases::size / 2; ++i)
			{
				TRY_CATCH_WRITE(container.push_back(test_case[ i ]))
			}

			write::container::to_file(container, *this->ofs);

			(*this->ofs) << std::endl;
		}

		void _test_pop_back(container_type &container)
		{
			(*this->ofs) << "pop_back()" << std::endl;

			write::container::to_file(container, *this->ofs);
			for (size_t i = 0; i < container.size() / 2; ++i)
			{
				TRY_CATCH_WRITE(container.pop_back());
			}
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << std::endl;
		}

		void _test_insert(container_type &container)
		{
			(*this->ofs) << "insert()" << std::endl;

			(*this->ofs) << "single element (1)" << std::endl;
			value_type *test_case = GET_TEST_CASE;

			std::srand(test_case[ 0 ]);

			write::container::to_file(container, *this->ofs);
			for (int i = 0; i < 20; ++i)
			{
				TRY_CATCH_WRITE(container.insert(container.begin() + container.size() / 2, test_case[ i ]));
			}
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "fill (2)" << std::endl;

			for (int i = 0; i < 20; ++i)
			{
				TRY_CATCH_WRITE(container.insert(container.begin() + container.size() / 2, i, test_case[ i ]));
			}
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "range (3)" << std::endl;

			container_type filled_container = container_type(test_case, test_case + test_cases::size);

			TRY_CATCH_WRITE(
					container.insert(container.begin(), filled_container.begin(),
									 filled_container.begin() + (filled_container.size() / 2))
			);
			write::container::to_file(container, *this->ofs);
			TRY_CATCH_WRITE(
					container.insert(container.end(), filled_container.begin(),
									 filled_container.begin() + (filled_container.size() / 2))
			);
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << std::endl;
		}

		void _test_erase(container_type &container)
		{
			(*this->ofs) << "erase()" << std::endl;
			write::container::to_file(container, *this->ofs);
			value_type *test_case = GET_TEST_CASE;
			std::srand(test_case[ 0 ]);

			(*this->ofs) << "single position (1)" << std::endl;

			for (int i = 0; i < 10; ++i)
			{
				TRY_CATCH_WRITE(container.erase(container.begin()));
				TRY_CATCH_WRITE(container.erase(container.end() - 1));
			}
			write::container::to_file(container, *this->ofs);

			(*this->ofs) << "range (2)" << std::endl;

			for (int i = 0; i < 10; ++i)
			{
				TRY_CATCH_WRITE(
						container.erase(container.begin(), container.begin() + (container.size() / 2))
				);
			}
			write::container::to_file(container, *this->ofs);
			(*this->ofs) << std::endl;
		}

		void _test_swap(container_type &container)
		{
			(*this->ofs) << "swap()" << std::endl;
			write::container::to_file(container, *this->ofs);

			container_type copy = container;
			container_type empty_container;

			container.swap(empty_container);
			write::container::to_file(container, *this->ofs);
			container.swap(copy);
			write::container::to_file(container, *this->ofs);
			container_type filled_container = FILL_CONTAINER_WITH_TEST_CASE;
			copy.swap(filled_container);
			write::container::to_file(copy, *this->ofs);

			(*this->ofs) << std::endl;
		}

		void _test_clear(container_type &container)
		{
			(*this->ofs) << "clear()" << std::endl;

			container.clear();

			(*this->ofs) << std::endl;
		}

	public:
		explicit modifiers_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("VectorModifiers")
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