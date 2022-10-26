/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity_test.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:39:45 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:39:46 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../i_base_test.hpp"
#include "../../utility/write.hpp"
#include "../../utility/test_cases.hpp"

namespace vector
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

			this->container = container_type();

			(*this->ofs) << "Testing with empty Container:" << std::endl;
			this->_test_reserve(this->container);
			this->_test_resize(this->container);

			value_type *test_case = test_cases::get_test_case(value_type());
			container_type range = container_type(test_case, test_case + test_cases::size);
			(*this->ofs) << "Testing with Container of size " << range.size() << std::endl;
			this->_test_reserve(range);
			(*this->ofs) << "Filling Container up again" << std::endl;
			range = container_type(test_case, test_case + test_cases::size);
			this->_test_resize(range);

			this->print_test_end();
		}

	private:
		void _test_reserve(container_type &container)
		{
			static const int one_million = 1000000;
			// Reserve
			(*this->ofs) << "Testing \'.reserve()\' on Container" << std::endl;
			for (size_t to_reserve_to = 10; to_reserve_to < one_million; to_reserve_to *= 2)
			{
				(*this->ofs) << "Reserving " << to_reserve_to << std::endl;
				container.reserve(to_reserve_to);
				(*this->ofs) << container.size() << std::endl;
			}
			write::container::to_file(container, (*this->ofs));
		}

		void _test_resize(container_type &container)
		{
			static const int one_million = 1000000;
			// Resize
			(*this->ofs) << "Testing \'.resize()\' on Container" << std::endl;
			for (size_t to_resize_to = 1; to_resize_to < one_million; to_resize_to *= 10)
			{
				(*this->ofs) << "Reserving " << to_resize_to << std::endl;
				container.resize(to_resize_to);
				(*this->ofs) << container.size() << ',' << container.capacity() << std::endl;
			}
			write::container::to_file(container, (*this->ofs));
		}

	public:
		explicit capacity_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("VectorCapacity")
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