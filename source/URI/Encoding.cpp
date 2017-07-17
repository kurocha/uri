//
//  Encoding.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Encoding.hpp"

namespace URI
{
	namespace Encoding
	{
		// Unreserved characters never need to be encoded.
		bool is_unreserved(unsigned char c)
		{
			if (c >= 'A' && c <= 'Z') return true;
			if (c >= 'a' && c <= 'z') return true;
			if (c >= '0' && c <= '9') return true;
			if (c == '_' || c == '-' || c == '.' || c == '~') return true;
			
			return false;
		}
		
		// In all contexts, these characters must be encoded.
		bool is_special(unsigned char c)
		{
			if (c <= 32) return true;
			if (c >= 127) return true;
			
			if (c == '#' || c == '%' || c == '+') return true;
			
			return false;
		}
		
		bool is_query_unreserved(unsigned char c)
		{
			return !is_special(c) && c != '?' && c != '&' && c != '=';
		}
		
		bool is_path_unreserved(unsigned char c)
		{
			return !is_special(c) && c != '?' && c != '/';
		}
		
		static char to_hex(unsigned value) {
			const char hex[] = "0123456789ABCDEF";
			
			if (value >= 16)
				throw std::out_of_range("value cannot be converted to hex");
			
			return hex[value];
		}
		
		static unsigned from_hex(char character) {
			if (character >= '0' && character <= '9')
				return character - '0';
			else if (character >= 'A' && character <= 'F')
				return 10 + (character - 'A');
			else if (character >= 'a' && character <= 'f')
				return 10 + (character - 'a');
			
			throw std::invalid_argument("not a hex character");
		}
		
		std::string encode(const std::string & input, bool(*is_safe)(unsigned char))
		{
			std::string output;
			output.reserve(input.size());
			
			for (auto c : input) {
				if (!is_safe(c)) {
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
}
