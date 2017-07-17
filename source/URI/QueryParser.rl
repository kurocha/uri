//
//  QueryParser.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <URI/QueryParser.hpp>

#include <URI/Encoding.hpp>

#include <iostream>

namespace URI
{
	namespace QueryParser
	{
		%%{
			machine QueryParser;
			
			action mark {
				mark = fpc;
			}
			
			action name {
				name = std::string(mark, fpc);
			}
			
			action value {
				value = std::string(mark, fpc);
			}
			
			action pair {
				named_values.insert({Encoding::decode(name), Encoding::decode(value)});
			}
			
			# An application/x-www-form-urlencoded parser as defined by WhatWG.
			# Based on https://url.spec.whatwg.org/#application/x-www-form-urlencoded
			
			pchar = any - [&=];
			
			# The WhatWG specs say this part could be empty, but it's pretty silly to have an empty key I think.
			name = (pchar+) >mark %name;
			value = (pchar*) >mark %value;
			
			name_value_pair = (name '=' value) %pair;
			
			main := ((name_value_pair '&')* name_value_pair)?;
			
			write data;
		}%%
		
		std::size_t parse(const Byte * begin, const Byte * end, NamedValues & named_values)
		{
			auto p = begin;
			auto pe = end;
			int cs = 0;
			
			const Byte * eof = pe;
			const Byte * mark = nullptr;
			
			std::string name, value;
			
			%%{
				write init;
				write exec;
			}%%
			
			return p-begin;
		}
	}
}
