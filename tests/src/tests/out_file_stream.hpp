/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file_stream.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:40:15 by tschmitt          #+#    #+#             */
/*   Updated: 2022/10/26 19:40:17 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>

class out_file_stream : public std::ofstream
{
private:
	std::string _file_name;
public:
	out_file_stream() : std::ofstream("bullshit"), _file_name("bullshit") { };

	explicit out_file_stream(
			const std::string &file_name,
			std::ios_base::openmode mode = ios_base::out
	) : std::ofstream(file_name, mode),
		_file_name(file_name) { };

	const std::string &get_file_name() const { return this->_file_name; }

};
