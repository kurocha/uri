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
			return !is_special(c) && c != '?' && c != SEPARATOR;
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
			std::string buffer;
			buffer.reserve(input.size());
			
			auto current = input.begin();
			auto end = input.end();
			
			while (current != end) {
				if (*current == '%') {
					if ((end - current) < 2)
						throw std::invalid_argument("invalid percent encoding!");
					
					char character = from_hex(*++current) * 16;
					character += from_hex(*++current);
					
					buffer += character;
				} else {
					buffer += *current;
				}
				
				++current;
			}
			
			return buffer;
		}
		
		std::string encode_path(const std::string & native_path, char separator, bool directory, bool(*is_safe)(unsigned char))
		{
			std::string buffer;
			buffer.reserve(native_path.size());
			
			auto current = native_path.begin();
			auto end = native_path.end();
			
			while (current != end) {
				if (*current == separator) {
					// Encode native separator as URI path separator:
					buffer += SEPARATOR;
				} else if (!is_safe(*current)) {
					// Otherwise, if it's an unsafe character, we encode it using percent-escape:
					auto value = (unsigned char)*current;
					buffer += '%';
					buffer += to_hex(value / 16);
					buffer += to_hex(value % 16);
				} else {
					// Otherwise it's fine to just append it:
					buffer += *current;
				}
				
				++current;
			}
			
			// If this is a directory, we append a trailing separator:
			if (directory && buffer.back() != SEPARATOR) {
				buffer += SEPARATOR;
			}
			
			return buffer;
		}
		
		std::string decode_path(const std::string & path, char separator)
		{
			std::string buffer;
			buffer.reserve(path.size());
			
			auto current = path.begin();
			auto end = path.end();
			
			while (current != end) {
				if (*current == '%') {
					if ((end - current) < 2)
						throw std::invalid_argument("invalid percent encoding!");
					
					char character = from_hex(*++current) * 16;
					character += from_hex(*++current);
					
					if (character == separator)
						throw std::invalid_argument("cannot represent encoded separator!");
					
					buffer += character;
				} else {
					buffer += *current;
				}
				
				++current;
			}
			
			return buffer;
		}
	}
}
