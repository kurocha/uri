//
//  Query.cpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Query.hpp"

#include <iostream>

namespace URI
{
	Query Query::operator+(const Query & other)
	{
		// Ensure neither side is empty:
		if (empty()) return other;
		if (other.empty()) return *this;
		
		// Join them together:
		return value + '&' + other.value;
	}
	
	std::ostream & operator<<(std::ostream & output, const Query & query)
	{
		if (query.empty()) return output;
		
		return output << '?' << query.value;
	}
}
