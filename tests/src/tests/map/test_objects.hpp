#pragma once

#include "../i_base_test.hpp"
#include "element_access_test.hpp"
#include "modifiers_test.hpp"
#include "operations_test.hpp"
#include "../generic/test_objects.hpp"

namespace map
{
	template < class ContainerSTD, class ContainerFT >
	struct test_objects
	{
		static i_base_test<ContainerSTD> *std[];
		static i_base_test<ContainerFT> *ft[];
	};

	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerSTD> *test_objects<ContainerSTD, ContainerFT>::std[] = {
			generic::test_objects<ContainerSTD, ContainerFT>::std[ 0 ],
			generic::test_objects<ContainerSTD, ContainerFT>::std[ 1 ],
			generic::test_objects<ContainerSTD, ContainerFT>::std[ 2 ],
			new map::element_access_test<ContainerSTD>(false),
			new map::modifiers_test<ContainerSTD>(false),
			new map::operations_test<ContainerSTD>(false)
	};
	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerFT> *test_objects<ContainerSTD, ContainerFT>::ft[] = {
			generic::test_objects<ContainerSTD, ContainerFT>::ft[ 0 ],
			generic::test_objects<ContainerSTD, ContainerFT>::ft[ 1 ],
			generic::test_objects<ContainerSTD, ContainerFT>::ft[ 2 ],
			new map::element_access_test<ContainerFT>(false),
			new map::modifiers_test<ContainerFT>(false),
			new map::operations_test<ContainerFT>(false)
	};
}