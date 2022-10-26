#pragma once

#include <ostream>
#include <fstream>

namespace write
{
	namespace color
	{
		namespace
		{
			enum code
			{
				FG_RED = 31,
				FG_GREEN = 32,
				FG_BLUE = 34,
				FG_BLACK = 30,
				FG_DEFAULT = 39,
				BG_RED = 41,
				BG_GREEN = 42,
				BG_BLUE = 44,
				BG_DEFAULT = 49
			};

			class modifier
			{
			private:
				code _color_code;
			public:
				explicit modifier(code color_code) : _color_code(color_code) { };

				friend std::ostream &operator<<(std::ostream &os, const modifier &modifier)
				{
					os << "\033[" << modifier._color_code << "m";
					return os;
				}
			};
		}
		namespace fg
		{
			static modifier red(FG_RED);
			static modifier green(FG_GREEN);
			static modifier blue(FG_BLUE);
			static modifier black(FG_BLACK);
			static modifier reset(FG_DEFAULT);
		}
		namespace bg
		{
			static modifier red(BG_RED);
			static modifier green(BG_GREEN);
			static modifier blue(BG_BLUE);
			static modifier reset(BG_DEFAULT);
		}

	}

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