//
//  GenericParser.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <URI/GenericParser.hpp>

namespace URI
{
	%%{
		machine GenericParser;
		
		action mark {
			mark = fpc;
		}
		
		action query {
			_generic.query = std::string(mark, fpc);
		}
		
		action fragment {
			_generic.fragment = std::string(mark, fpc);
		}
		
		action path {
			_generic.path = std::string(mark, fpc);
		}
		
		action port {
			_generic.port = std::string(mark, fpc);
		}
		
		action host {
			_generic.host = std::string(mark, fpc);
		}
		
		action userinfo {
			_generic.userinfo = std::string(mark, fpc);
		}
		
		action scheme {
			_generic.scheme = std::string(mark, fpc);
		}
		
		action error {
			throw std::invalid_argument("could not parse uri");
		}
		
		# A URI parser as defined by RFC3986.
		# Based on https://tools.ietf.org/html/rfc3986
		
		include RFC3986 "RFC3986.rl";
		
		query = (pchar | "/" | "?")* >mark %query;
		fragment = (pchar | "/" | "?")* >mark %fragment;

		segment = pchar*;
		segment_nz = pchar+;
		
		# segment_nz_nc = (unreserved | percent_encoded | subcomponent_delimiters | "@")+;
		segment_nz_nc = (pchar - ":")+;

		path_abempty = (("/" segment)*) >mark %path;
		path_absolute = ("/" (segment_nz ("/" segment)*)?) >mark %path;
		path_noscheme = (segment_nz_nc ("/" segment)*) >mark %path;
		path_rootless = (segment_nz ("/" segment)*) >mark %path;
		path_empty = "";

		regular_name = (unreserved | percent_encoded | subcomponent_delimiters)*;

		port = digit* >mark %port;
		host = (address_literal | address_ipv4 | regular_name) >mark %host;
		userinfo = (unreserved | percent_encoded | subcomponent_delimiters | ":")* >mark %userinfo;
		authority = (userinfo "@")? host (":" port)?;

		scheme = alpha >mark (alpha | digit | "+" | "-" | ".")* %scheme;

		# path = (path_abempty | path_absolute | path_noscheme | path_rootless | path_empty) >mark %path;

		relative_part =
			"//" authority path_abempty |
			path_absolute |
			path_noscheme |
			path_empty;

		hierarchy_part =
			"//" authority path_abempty |
			path_absolute |
			path_rootless |
			path_empty;

		relative = relative_part ("?" query)? ("#" fragment)?;
		absolute = scheme ":" hierarchy_part ("?" query)? ("#" fragment)?;
		
		uri = relative | absolute @err(error);
		
		main := uri;
		
		access this->_;
		
		write data;
	}%%
	
	GenericParser::GenericParser(Generic & generic) : _generic(generic)
	{
		%%{
			write init;
		}%%
	}
	
	GenericParser::~GenericParser()
	{
	}
	
	std::size_t GenericParser::parse(const Byte * begin, const Byte * end)
	{
		auto p = begin;
		auto pe = end;
		
		const Byte * eof = pe;
		const Byte * mark = nullptr;
		
		%%{
			write exec;
		}%%
		
		return p-begin;
	}
}
