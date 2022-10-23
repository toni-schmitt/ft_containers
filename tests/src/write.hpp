#pragma once

#include <ostream>
#include <fstream>

namespace write
{
	struct container
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
	};
}