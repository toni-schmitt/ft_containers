/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_objects.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:39:25 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:39:27 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include "../generic/test_objects.hpp"
#include "modifiers_test.hpp"
#include "operations_test.hpp"
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
	i_base_test<ContainerSTD> *test_objects<ContainerSTD, ContainerFT>::std[] = {
			new generic::capacity_test<ContainerSTD>(false),
			new generic::construction_test<ContainerSTD>(false),
			new generic::iterator_test<ContainerSTD>(false),
			new set::modifiers_test<ContainerSTD>(false),
			new set::operations_test<ContainerSTD>(false),
			NULL
	};
	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerFT> *test_objects<ContainerSTD, ContainerFT>::ft[] = {
			new generic::capacity_test<ContainerFT>(false),
			new generic::construction_test<ContainerFT>(false),
			new generic::iterator_test<ContainerFT>(false),
			new set::modifiers_test<ContainerFT>(false),
			new set::operations_test<ContainerFT>(false),
			NULL
	};
}