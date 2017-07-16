//
//  Relative.hpp
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
	class Relative
	{
	public:
		static Relative parse(const std::string &);
		
		Relative(const Generic & generic);
		Relative(const Path & path, const std::string & query = "", const std::string & fragment = "");
		virtual ~Relative();
		
		Generic generic() const noexcept;
		
		const Path & path() const noexcept {return _path;}
		const std::string & query() const noexcept {return _query;}
		const std::string & fragment() const noexcept {return _fragment;}
		
		Relative operator+(const Relative & other);
		
	private:
		Path _path;
		std::string _query;
		std::string _fragment;
	};
	
	std::ostream & operator<<(std::ostream &, const Relative &);
}
