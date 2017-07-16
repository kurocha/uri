//
//  Parser.hpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Generic.hpp"

namespace URI
{
	typedef unsigned char Byte;
	
	class Parser
	{
	public:
		Parser(Generic & generic);
		virtual ~Parser();
		
		std::size_t parse(const Byte * begin, const Byte * end);
		
		void parse(const std::string & string) {
			auto result = parse((const Byte *)string.data(), (const Byte *)string.data() + string.size());
			
			if (result != string.size())
				throw std::invalid_argument("could not parse uri completely");
		}
	
	private:
		Generic & _generic;
		
		int _cs;
	};
}
