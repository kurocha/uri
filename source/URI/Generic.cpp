//
//  Generic.cpp
//  File file is part of the "Uri" project and released under the MIT License.
//
//  Created by Samuel Williams on 13/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Generic.hpp"

#include "GenericParser.hpp"

#include <stdexcept>

namespace URI
{
	Generic Generic::parse(const std::string & value)
	{
		using namespace GenericParser;
		
		Generic generic;
		
		auto result = GenericParser::parse((const Byte *)value.data(), (const Byte *)value.data() + value.size(), generic);
		
		if (result != value.size())
			throw std::invalid_argument("could not parse entire string");
		
		return generic;
	}
	
	std::ostream & operator<<(std::ostream & output, const Generic & generic)
	{
		if (!generic.scheme.empty()) {
			output << generic.scheme << ":";
		}
		
		if (!generic.host.empty()) {
			output << "//";
			
			if (!generic.userinfo.empty()) {
				output << generic.userinfo << '@';
			}
			
			output << generic.host;
			
			if (!generic.port.empty()) {
				output << ':' << generic.port;
			}
		}
		
		output << generic.path;
		output << generic.query;
		
		if (!generic.fragment.empty()) {
			output << '#' << generic.fragment;
		}
		
		return output;
	}
	
	bool Generic::operator==(const Generic & other) const noexcept
	{
		return scheme == other.scheme && userinfo == other.userinfo && host == other.host && port == other.port && path == other.path && query == other.query && fragment == other.fragment;
	}
	
	bool Generic::operator!=(const Generic & other) const noexcept
	{
		return !(*this == other);
	}
	
	Generic Generic::operator+(const Generic & other)
	{
		if (other.is_absolute()) {
			return other;
		}
		
		Generic result = *this;
		
		result.query = other.query;
		result.fragment = other.fragment;
		
		if (other.path.is_absolute()) {
			result.path = other.path;
		} else {
			result.path = path + other.path;
		}
		
		return result;
	}
}
