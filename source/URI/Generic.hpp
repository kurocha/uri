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
		static Generic parse(const std::string & value);
		
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
		
		Generic operator+(const Generic & other);
	};
	
	// According to https://tools.ietf.org/html/rfc3986#section-3.3, we escape non-pchar using % encoding.
	std::string encode(const std::string & string);
	std::string decode(const std::string & string);
	
	std::ostream & operator<<(std::ostream &, const Generic &);
}
