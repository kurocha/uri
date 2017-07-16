//
//  Relative.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Relative.hpp"

#include "Parser.hpp"

#include <cassert>
#include <iostream>

namespace URI
{
	Relative Relative::parse(const std::string & value)
	{
		Generic generic;
		Parser parser(generic);
		
		parser.parse(value);
		
		// TODO perhaps throw std::invalid_argument and same for Absolute::parse.
		assert(generic.is_relative());
		
		return generic;
	}
	
	Relative::Relative(const Generic & generic) : _path(decode(generic.path)), _query(generic.query), _fragment(generic.fragment)
	{
	}
	
	Relative::Relative(const Path & path, const std::string & query, const std::string & fragment) : _path(path), _query(query), _fragment(fragment)
	{
	}
	
	Relative::~Relative()
	{
	}
	
	Generic Relative::generic() const noexcept
	{
		return {"", "", "", "", encode(_path.value()), _query, _fragment};
	}
	
	Relative Relative::operator+(const Relative & other)
	{
		return {_path + other.path(), _query, _fragment};
	}
	
	std::ostream & operator<<(std::ostream & output, const Relative & relative)
	{
		output << relative.path();
		
		const auto & query = relative.query();
		
		if (!query.empty()) {
			output << '?' << query;
		}
		
		const auto & fragment = relative.fragment();
		
		if (!fragment.empty()) {
			output << '#' << fragment;
		}
		
		return output;
	}
}
