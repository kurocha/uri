//
//  Absolute.hpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Path.hpp"
#include "Generic.hpp"

namespace URI
{
	class Relative;
	
	/// An absolute URI with a scheme/host part.
	class Absolute
	{
	public:
		static Absolute parse(const std::string &);
		
		Absolute(const Generic & generic);
		virtual ~Absolute();
		
		Absolute operator+(const Absolute & other) {return other;}
		Absolute operator+(const Relative & other);
		
		const Generic & generic() const noexcept {return _generic;}
		const Path & path() const noexcept {return _path;}
		
	private:
		Generic _generic;
		Path _path;
	};
	
	std::ostream & operator<<(std::ostream &, const Absolute &);
}
