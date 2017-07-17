//
//  Query.hpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <string>

namespace URI
{
	/// Assumes application/x-www-form-urlencoded.
	struct Query
	{
		Query() {}
		
		template <typename ValueT>
		Query(const ValueT & value_) : value(value_) {}
		
		std::string value;
		
		bool empty () const noexcept {return value.empty();}
		explicit operator bool() const noexcept {return !empty();}
		
		Query operator+(const Query & other);
		
		bool operator==(const Query & other) const {return value == other.value;}
		bool operator!=(const Query & other) const {return value != other.value;}
		bool operator<(const Query & other) const {return value < other.value;}
		bool operator<=(const Query & other) const {return value <= other.value;}
		bool operator>(const Query & other) const {return value > other.value;}
		bool operator>=(const Query & other) const {return value >= other.value;}
	};
	
	std::ostream & operator<<(std::ostream & output, const Query & query);
}
