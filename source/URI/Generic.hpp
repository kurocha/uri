//
//  Generic.hpp
//  File file is part of the "Uri" project and released under the MIT License.
//
//  Created by Samuel Williams on 13/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Path.hpp"
#include "Query.hpp"

#include <string>
#include <iosfwd>

namespace URI
{
	struct Generic
	{
		Generic() = default;
		Generic(const Generic &) = default;
		Generic(Generic &&) = default;
		
		Generic(const unsigned char * begin, const unsigned char * end);
		
		using Byte = unsigned char;
		
		// Parse the given string.
		Generic(const std::string & value) : Generic(reinterpret_cast<const Byte *>(value.data()), reinterpret_cast<const Byte *>(value.data()) + value.size()) {}
		
		template <std::size_t SIZE>
		Generic(const char (&value)[SIZE]) : Generic(reinterpret_cast<const Byte *>(value), reinterpret_cast<const Byte *>(value) + SIZE - 1) {}
		
		std::string scheme;
		std::string userinfo;
		std::string host;
		std::string port;
		Path path;
		Query query;
		std::string fragment;
		
		/// A relative URI is any URI that doesn't explicitly specify the protocol/host, and must be resolved relative to a absolute URI.
		bool is_relative() const noexcept {return scheme.empty() && host.empty();}
		bool is_absolute() const noexcept {return !is_relative();}
		
		bool operator==(const Generic & other) const noexcept;
		bool operator!=(const Generic & other) const noexcept;
		
		Generic operator+(const Generic & other) const;
	};
	
	std::ostream & operator<<(std::ostream &, const Generic &);
}
