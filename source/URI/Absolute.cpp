//
//  Absolute.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Absolute.hpp"

#include "Relative.hpp"
#include "Parser.hpp"

#include <cassert>
#include <iostream>

namespace URI
{
	Absolute Absolute::parse(const std::string & value)
	{
		Generic generic;
		Parser parser(generic);
		
		parser.parse(value);
		
		return generic;
	}
	
	Absolute::Absolute(const Generic & generic) : _generic(generic), _path(decode(generic.path))
	{
		assert(generic.is_absolute());
	}
	
	Absolute::~Absolute()
	{
	}
	
	Absolute Absolute::operator+(const Relative & other)
	{
		Generic generic = _generic;
		
		if (other.path().is_relative()) {
			generic.path = (_path + other.path()).value();
		} else {
			generic.path = other.path().value();
		}
		
		generic.query = other.generic().query;
		generic.fragment = other.generic().fragment;
		
		return generic;
	}
	
	std::ostream & operator<<(std::ostream & output, const Absolute & absolute)
	{
		return output << absolute.generic();
	}
}
