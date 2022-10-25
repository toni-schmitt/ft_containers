#pragma once

#include "../i_base_test.hpp"

namespace set
{
	template < class ContainerSTD, class ContainerFT >
	struct test_objects
	{
		static i_base_test<ContainerSTD> *std[];
		static i_base_test<ContainerFT> *ft[];
	};

	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerSTD> *test_objects<ContainerSTD, ContainerFT>::std[] = { NULL };
	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerFT> *test_objects<ContainerSTD, ContainerFT>::ft[] = { NULL };
}