/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_objects.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:40:19 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:40:23 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "generic/test_objects.hpp"
#include "vector/test_objects.hpp"
#include "map/test_objects.hpp"
#include "set/test_objects.hpp"
#include "stack/test_objects.hpp"

template < class ContainerSTD, class ContainerFT >
static void delete_test_object(i_base_test<ContainerSTD> *std_objects[], i_base_test<ContainerFT> *ft_objects[])
{
	for (int i = 0; std_objects[ i ]; ++i)
	{
		delete std_objects[ i ];
		std_objects[ i ] = NULL;
	}
	for (int i = 0; ft_objects[ i ]; ++i)
	{
		delete ft_objects[ i ];
		ft_objects[ i ] = NULL;
	}
}

void delete_test_objects()
{
	typedef ft_namespace::namespace_chooser::vector ft_vector;
	typedef ft_namespace::namespace_chooser::map ft_map;
	typedef ft_namespace::namespace_chooser::stack ft_stack;
	typedef ft_namespace::namespace_chooser::set ft_set;
	typedef std_namespace::namespace_chooser::vector std_vector;
	typedef std_namespace::namespace_chooser::map std_map;
	typedef std_namespace::namespace_chooser::stack std_stack;
	typedef std_namespace::namespace_chooser::set std_set;

	delete_test_object(generic::test_objects<std_vector, ft_vector>::std,
					   generic::test_objects<std_vector, ft_vector>::ft);
	delete_test_object(generic::test_objects<std_map, ft_map>::std, generic::test_objects<std_map, ft_map>::ft);
	delete_test_object(generic::test_objects<std_set, ft_set>::std, generic::test_objects<std_set, ft_set>::ft);

	delete_test_object(vector::test_objects<std_vector, ft_vector>::std,
					   vector::test_objects<std_vector, ft_vector>::ft);

	delete_test_object(map::test_objects<std_map, ft_map>::std, map::test_objects<std_map, ft_map>::ft);

	delete_test_object(set::test_objects<std_set, ft_set>::std, set::test_objects<std_set, ft_set>::ft);

	delete_test_object(stack::test_objects<std_stack, ft_stack>::std, stack::test_objects<std_stack, ft_stack>::ft);
}