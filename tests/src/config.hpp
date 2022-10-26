/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:42:26 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:56:01 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* Config File */

#define AVAILABLE_TESTS \
	/* Static Member Initialization */ \
	\
	/* Available Tests */ \
	/* Vector */ \
	const int test::available_tests::vector_size = 6; \
	std::string test::available_tests::vector[] = { \
			"generic_construction", \
			"generic_capacity", \
			"generic_iterator", \
			"capacity", \
			"element_access", \
			"modifiers", \
	}; \
	/* Map */ \
	const int test::available_tests::map_size = 6; \
	std::string test::available_tests::map[] = { \
			"generic_construction", \
			"generic_capacity", \
			"generic_iterator", \
			"element_access", \
			"modifiers", \
			"operations" \
	}; \
	/* Set */ \
	const int test::available_tests::set_size = 5; \
	std::string test::available_tests::set[] = { \
			"generic_construction", \
			"generic_capacity", \
			"generic_iterator", \
			"modifiers", \
			"operations" \
	}; \
	/* Stack */ \
	const int test::available_tests::stack_size = 3; \
	std::string test::available_tests::stack[] = { \
			"capacity", \
			"element_access", \
			"modifiers" \
	};