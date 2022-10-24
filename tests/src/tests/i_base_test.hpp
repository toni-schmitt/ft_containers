#pragma once

#include "out_file_stream.hpp"

template < class Container >
class i_base_test
{
public:
	virtual void test(out_file_stream *ofs) = 0;

protected:
	typedef Container container_type;
	typedef typename container_type::value_type value_type;

	out_file_stream *ofs;
	std::string test_name;
	container_type container;

	explicit i_base_test(const std::string &test_name) : ofs(NULL), test_name(test_name) { }

	explicit i_base_test(
			out_file_stream &ofs, const std::string &test_name
	) : ofs(new out_file_stream(ofs.get_file_name())), test_name(test_name) { }

	~i_base_test() { delete ofs; }

	void update_ofs(out_file_stream *new_ofs)
	{
		const std::string &file_name = new_ofs->get_file_name();
		delete this->ofs;
		this->ofs = new out_file_stream(file_name);
	}

	void print_test_start()
	{
		(*this->ofs) << "Running Tests for " << test_name << " (Generic Container)" << std::endl;
	}

	void print_test_end()
	{
		(*this->ofs) << "Done with Tests for " << test_name << " (Generic Container)" << std::endl;
	}
};