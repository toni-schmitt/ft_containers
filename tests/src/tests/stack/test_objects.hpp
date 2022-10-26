/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_objects.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:39:41 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:39:42 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "capacity_test.hpp"
#include "element_access_test.hpp"
#include "modifiers_test.hpp"
#include "../i_base_test.hpp"

namespace stack
{
	template < class ContainerSTD, class ContainerFT >
	struct test_objects
	{
		static i_base_test<ContainerSTD> *std[];
		static i_base_test<ContainerFT> *ft[];
	};

	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerSTD> *test_objects<ContainerSTD, ContainerFT>::std[] = {
			new stack::capacity_test<ContainerSTD>(false),
			new stack::element_access_test<ContainerSTD>(false),
			new stack::modifiers_test<ContainerSTD>(false),
			NULL
	};
	template < class ContainerSTD, class ContainerFT >
	i_base_test<ContainerFT> *test_objects<ContainerSTD, ContainerFT>::ft[] = {
			new stack::capacity_test<ContainerFT>(false),
			new stack::element_access_test<ContainerFT>(false),
			new stack::modifiers_test<ContainerFT>(false),
			NULL
	};
}