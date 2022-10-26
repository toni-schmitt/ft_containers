#pragma once

#include <string>
#include <ostream>
#include <fstream>
#include "tests/out_file_stream.hpp"
#include "tests/test_objects.hpp"
#include <exception>

#define TIME(x) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(x));
#define TIME_DIFF(start, end) (1000.0 * (end).tv_sec + 1e-6 * (end).tv_nsec - (1000.0 * (start).tv_sec + 1e-6 * (start).tv_nsec));

namespace tester
{
	static const std::string file_name_prefix = "./logs/";

	struct test
	{
		typedef std_namespace::namespace_chooser::vector std_vector;
		typedef ft_namespace::namespace_chooser::vector ft_vector;
		typedef std_namespace::namespace_chooser::map std_map;
		typedef ft_namespace::namespace_chooser::map ft_map;
		typedef std_namespace::namespace_chooser::set std_set;
		typedef ft_namespace::namespace_chooser::set ft_set;
		typedef std_namespace::namespace_chooser::stack std_stack;
		typedef ft_namespace::namespace_chooser::stack ft_stack;

	public:
		static void run(const std::string &container, const std::string &test)
		{
			if (container == "vector")
			{
				std::cout << "Testing Vector" << std::endl;
				typedef vector::test_objects<std_vector, ft_vector> vector_test_objects;
				_run<std_vector, ft_vector>(test, available_tests::vector, available_tests::vector_size,
											vector_test_objects::std,
											vector_test_objects::ft);
				return;
			}
			if (container == "map")
			{
				std::cout << "Testing Map" << std::endl;
				typedef map::test_objects<std_map, ft_map> map_test_objects;
				_run<std_map, ft_map>(test, available_tests::map, available_tests::map_size,
									  map_test_objects::std,
									  map_test_objects::ft);
				return;
			}
			if (container == "set")
			{
				std::cout << "Testing Set" << std::endl;
				typedef set::test_objects<std_set, ft_set> set_test_objects;
				_run<std_set, ft_set>(test, available_tests::set, available_tests::set_size,
									  set_test_objects::std,
									  set_test_objects::ft);
				return;
			}
			if (container == "stack")
			{
				std::cout << "Testing Stack" << std::endl;
				typedef stack::test_objects<std_stack, ft_stack> stack_test_objects;
				_run<std_stack, ft_stack>(test, available_tests::stack, available_tests::stack_size,
										  stack_test_objects::std,
										  stack_test_objects::ft);
				return;
			}
			throw std::logic_error(container + " is an invalid Container");
		}

	private:
		static const size_t _invalid_test_case = -1;

		template < class ContainerSTD, class ContainerFT >
		static void _run(
				const std::string &test, const std::string available_tests[], const size_t &available_tests_size,
				i_base_test<ContainerSTD> *std_test_objects[], i_base_test<ContainerFT> *ft_test_objects[]
		)
		{
			if (test == "all" || test.empty())
			{
				for (size_t i = 0; i < available_tests_size; ++i)
				{
					_run_test_case<ContainerSTD, ContainerFT>(
							available_tests[ i ], std_test_objects[ i ], ft_test_objects[ i ]
					);
				}
			}
			else
			{
				size_t index = _get_test_case_index(test, available_tests, available_tests_size);
				if (index == _invalid_test_case)
					throw std::logic_error(test + " is an invalid Test Case");
				_run_test_case<ContainerSTD, ContainerFT>(
						available_tests[ index ], std_test_objects[ index ], ft_test_objects[ index ]
				);
			}
		}

		static size_t _get_test_case_index(const std::string &test_case, const std::string available_tests[],
										   const size_t &available_tests_size)
		{
			size_t index = _invalid_test_case;
			for (size_t i = 0; i < available_tests_size; ++i)
			{
				if (available_tests[ i ] == test_case)
				{
					index = i;
					break;
				}
			}
			return index;
		}

		template < class ContainerSTD, class ContainerFT >
		static void _run_test_case(
				const std::string &test, i_base_test<ContainerSTD> *std_test_object,
				i_base_test<ContainerFT> *ft_test_object
		)
		{
			std::cout << "Testing " << test << std::endl;

			struct timespec std_start_time = { };
			TIME(std_start_time);

			std::string std_log = _run_test_case(test + "_std.log", std_test_object);

			struct timespec std_end_time = { };
			TIME(std_end_time);

			struct timespec ft_start_time = { };
			TIME(ft_start_time);

			std::string ft_log = _run_test_case(test + "_ft.log", ft_test_object);

			struct timespec ft_end_time = { };
			TIME(ft_end_time);

			bool test_succeeded = compare_files(std_log, ft_log);
			std::cout << test << ':' << (test_succeeded ? "Success" : "Failure") << std::endl;

			double std_duration = TIME_DIFF(std_start_time, std_end_time);
			double ft_duration = TIME_DIFF(ft_start_time, ft_end_time);

			std::cout << "STD Containers took: " << std_duration << "ms" << std::endl;
			std::cout << "FT Containers took: " << ft_duration << "ms" << std::endl;
			std::cout << "Benchmark: " << (ft_duration > std_duration * 20.0 ? "Fail" : "Success") << std::endl;
		}

		template < class TestObject >
		static std::string _run_test_case(const std::string &test, TestObject test_object)
		{
			std::string test_file_name = file_name_prefix + test;
			out_file_stream ofs(test_file_name, std::ofstream::out);
			try
			{
				test_object->test(&ofs);
			}
			catch (std::exception &e)
			{
				ofs << "Failure, Exception: " << e.what() << std::endl;
				ofs.close();
				return test_file_name;
			}
			catch (...)
			{
				ofs << "Failure, Unknown Exception" << std::endl;
				ofs.close();
				return test_file_name;
			}
			ofs << "Success" << std::endl;
			ofs.close();
			return test_file_name;
		}


		struct available_tests
		{
			static const int vector_size = 6;
			static std::string vector[vector_size];
			static const int map_size = 6;
			static std::string map[map_size];
			static const int set_size = 0;
			static std::string set[set_size];
			static const int stack_size = 3;
			static std::string stack[stack_size];
		};
	};

	/* Static Member Initialization */

	/* Available Tests */
	/* Vector */
	std::string test::available_tests::vector[] = {
			"generic_construction",
			"generic_capacity",
			"generic_iterator",
			"capacity",
			"element_access",
			"modifiers",
	};
	/* Map */
	std::string test::available_tests::map[] = {
			"generic_construction",
			"generic_capacity",
			"generic_iterator",
			"element_access",
			"modifiers",
			"operations"
	};
	/* Set */
	std::string test::available_tests::set[] = { };
	/* Stack */
	std::string test::available_tests::stack[] = {
			"capacity",
			"element_access",
			"modifiers"
	};
}
