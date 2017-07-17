//
//  QueryParser.hpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <string>
#include <map>

namespace URI
{
	namespace QueryParser
	{
		using Byte = unsigned char;
		using NamedValues = std::multimap<std::string, std::string>;
		
		std::size_t parse(const Byte * begin, const Byte * end, NamedValues & named_values);
	}
}
