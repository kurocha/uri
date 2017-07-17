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
	namespace GenericParser
	{
		%%{
			machine GenericParser;
			
			action mark {
				mark = fpc;
			}
			
			action query {
				generic.query = std::string(mark, fpc);
			}
			
			action fragment {
				generic.fragment = std::string(mark, fpc);
			}
			
			action path {
				generic.path = std::string(mark, fpc);
			}
			
			action port {
				generic.port = std::string(mark, fpc);
			}
			
			action host {
				generic.host = std::string(mark, fpc);
			}
			
			action userinfo {
				generic.userinfo = std::string(mark, fpc);
			}
			
			action scheme {
				generic.scheme = std::string(mark, fpc);
			}
			
			action error {
				throw std::invalid_argument("could not parse uri");
			}
			
			# A URI parser as defined by RFC3986.
			# Based on https://tools.ietf.org/html/rfc3986
			
			include RFC3986 "RFC3986.rl";
			
			main := uri;
			
			write data;
		}%%
		
		std::size_t parse(const Byte * begin, const Byte * end, Generic & generic)
		{
			auto p = begin;
			auto pe = end;
			int cs = 0;
			
			const Byte * eof = pe;
			const Byte * mark = nullptr;
			
			%%{
				write init;
				write exec;
			}%%
			
			return p-begin;
		}
	}
}
