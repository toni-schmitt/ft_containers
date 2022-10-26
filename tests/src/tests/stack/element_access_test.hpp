/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_access_test.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:39:33 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:39:35 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace stack
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

			{
				typedef typename container_type::container_type underlying_container;
				value_type *test_case = GET_TEST_CASE;
				underlying_container cntr = underlying_container(test_case, test_case + test_cases::size);
				this->container = container_type(cntr);
			}

			for (size_t i = 0; i < this->container.size() / 2; ++i)
			{
				TRY_CATCH_WRITE(
						(*this->ofs) << this->container.top() << ','
				)
				TRY_CATCH_WRITE(
						(*this->ofs) << (this->container.top() -= i) << ','
				)
			}
			this->_write_to_file(this->container);

			this->print_test_end();
		}

	private:
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
		explicit element_access_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("StackElementAccess")
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