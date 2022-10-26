/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_base_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:40:11 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:40:13 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "out_file_stream.hpp"

/**
 * @brief Abstract Class 'i_base_test' that defines the basic Structure of every Test used in this Tester
 * @tparam Container Container to use in the Test
 */
template < class Container >
class i_base_test
{
public:
	/**
	 * @brief Runs the test
	 * @param ofs out_file_stream (wrapper to std::ofstream) to write the output to
	 */
	virtual void test(out_file_stream *ofs) = 0;

	virtual ~i_base_test() { delete this->ofs; }

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