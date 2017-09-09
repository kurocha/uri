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
		
		Generic & operator=(const Generic & other) = default;
		
		Generic(const char * begin, const char * end);
		
		// Parse the given string.
		Generic(const std::string & value) : Generic(value.data(), value.data() + value.size()) {}
		
		// We subtract 1 since it includes the null terminator.
		template <std::size_t SIZE>
		Generic(const char (&value)[SIZE]) : Generic(value, value + SIZE - 1) {}
		
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
		
		bool operator<(const Generic & other) const noexcept;
		
		Generic operator+(const Generic & other) const;
		
		bool empty() const noexcept {return host.empty() && path.empty();}
		explicit operator bool() const noexcept {return !empty();}
		
		// Extract the host part of the URI. Unwraps the square brackets around IPv6 addresses.
		std::string hostname() const;
		
	protected:
		Generic(
			const std::string & scheme_,
			const std::string & userinfo_,
			const std::string & host_,
			const std::string & port_,
			const Path & path_,
			const Query & query_,
			const std::string & fragment_
		) : scheme(scheme_), userinfo(userinfo_), host(host_), port(port_), path(path_), query(query_), fragment(fragment_) {}
	};
	
	std::ostream & operator<<(std::ostream &, const Generic &);
}
