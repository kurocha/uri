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
#include <iostream>

namespace URI
{
	Generic Generic::parse(const std::string & value)
	{
		Generic generic;
		GenericParser parser(generic);
		
		parser.parse(value);
		
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
	
	bool is_pchar(unsigned char c)
	{
		// The following characters are pchar: [a-zA-Z0-9_\-\.~!$&'()*+,;=:@\/]
		// [33, 36, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 95, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 126]
		
		if (c == 33 || c == 36) return true;
		if (c >= 62 && c < 64) return false;
		if (c >= 38 && c <= 90) return true;
		if (c == 95) return true;
		if (c >= 97 && c <= 122) return true;
		if (c == 126) return true;
		
		return false;
	}
	
	char to_hex(unsigned value) {
		const char hex[] = "0123456789ABCDEF";
		
		if (value >= 16)
			throw std::out_of_range("value cannot be converted to hex");
		
		return hex[value];
	}
	
	unsigned from_hex(char character) {
		if (character >= '0' && character <= '9')
			return character - '0';
		else if (character >= 'A' && character <= 'F')
			return 10 + (character - 'A');
		else if (character >= 'a' && character <= 'f')
			return 10 + (character - 'a');
		
		throw std::invalid_argument("not a hex character");
	}
	
	std::string encode(const std::string & input)
	{
		std::string output;
		output.reserve(input.size());
		
		for (auto c : input) {
			if (!is_pchar(c)) {
				output += '%';
				
				auto value = (unsigned char)c;
				output += to_hex(value / 16);
				output += to_hex(value % 16);
			} else {
				output += c;
			}
		}
		
		return output;
	}
	
	std::string decode(const std::string & input)
	{
		std::string output;
		output.reserve(input.size());
		
		auto i = input.begin();
		for (; i < input.end() - 2; i++) {
			if (*i == '%') {
				char character = from_hex(*++i) * 16;
				character += from_hex(*++i);
				
				output += character;
			} else {
				output += *i;
			}
		}
		
		for (; i < input.end(); i++) {
			if (*i == '%') throw std::invalid_argument("invalid percent encoding");
			
			output += *i;
		}
		
		return output;
	}
}
