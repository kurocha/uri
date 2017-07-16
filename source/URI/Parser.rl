//
//  Parser.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <URI/Parser.hpp>

namespace URI
{
	%%{
		machine Parser;
		
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
		
		include RFC3986 "RFC3986.rl";
		
		main := uri;
		
		access this->_;
		
		write data;
	}%%
	
	Parser::Parser(Generic & generic) : _generic(generic)
	{
		%%{
			write init;
		}%%
	}
	
	Parser::~Parser()
	{
	}
	
	std::size_t Parser::parse(const Byte * begin, const Byte * end)
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
