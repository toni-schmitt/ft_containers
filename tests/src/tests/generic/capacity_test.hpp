/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity_test.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:38:39 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:38:40 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace generic
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

			// Empty
			(*this->ofs) << "Check if this->container is empty" << std::endl;
			(*this->ofs) << this->container.empty() << std::endl;
			value_type *test_case = test_cases::get_test_case(value_type());
			container_type range = container_type(test_case, test_case + test_cases::size);
			(*this->ofs) << "Check if newly filled container \'range\' is empty" << std::endl;
			(*this->ofs) << range.empty() << std::endl;

			// Size
			(*this->ofs) << "Checking size of this->container" << std::endl;
			(*this->ofs) << this->container.size() << std::endl;
			(*this->ofs) << "Checking size of \'range\'" << std::endl;
			(*this->ofs) << range.size() << std::endl;

			// Max Size
			(*this->ofs) << "Checking max_size of \'this->container\'" << std::endl;
			(*this->ofs) << this->container.max_size() << std::endl;
			(*this->ofs) << "Checking max_size of \'range\'" << std::endl;
			(*this->ofs) << range.max_size() << std::endl;
			(*this->ofs) << "Comparing max_size of \'this->container\' and \'range\'" << std::endl;
			(*this->ofs) << (this->container.max_size() == range.max_size()) << std::endl;

			this->print_test_end();
		}

		explicit capacity_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("Capacity")
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