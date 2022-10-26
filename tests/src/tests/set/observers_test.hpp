#pragma once

#include "../i_base_test.hpp"
#include "../../utility/test_cases.hpp"

namespace set
{
	template < class Container >
	struct observers_test : public i_base_test<Container>
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

			this->print_test_end();
		}

	private:
	public:
		explicit observers_test(
				bool run_test_in_constructor = true
		) : i_base_test<Container>("SetObservers")
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