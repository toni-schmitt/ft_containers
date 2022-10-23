#pragma once

#include <ostream>
#include <fstream>

namespace write
{
	namespace container
	{
		template < class Container >
		static void to_file(Container container, std::ofstream &out_file_stream)
		{
			out_file_stream << std::endl;
			for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
			{
				out_file_stream << *it << ',';
			}
			out_file_stream << std::endl;
		}

		template < class Container >
		static void to_out(Container container, std::ostream &out_stream)
		{
			out_stream << "Printing Content of Container" << std::endl;
			for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
			{
				out_stream << *it << ", ";
			}
			out_stream << std::endl;
		}
	}

	namespace iterator
	{
		template < class Iterator >
		static void to_file(Iterator iterator, Iterator end, std::ofstream &out_file_stream)
		{
			if (iterator == end)
				return;

			out_file_stream << '<' << *iterator << '>' << std::endl;
		}

		template < class Iterator >
		static void to_out(Iterator iterator, Iterator end, std::ostream &out_stream)
		{
			if (iterator == end)
				return;

			out_stream << '<' << *iterator << '>' << std::endl;
		}
	}
}