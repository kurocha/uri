//
//  Path.hpp
//  File file is part of the "Uri" project and released under the MIT License.
//
//  Created by Samuel Williams on 13/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <string>
#include <iosfwd>

namespace URI
{
	class Path {
	public:
		constexpr static const char SEPARATOR = '/';

	public:
		Path();
		Path(const std::string & value);
		Path(const char * value);

		const std::string & value() const noexcept {return _value;}

		bool empty () const {return _value.size() == 0;}
		explicit operator bool() const {return !empty();}
		
		/// Does the path begin with a "/"?
		bool is_absolute() const;
		bool is_relative() const {return !is_absolute();}

		/// Does the path end with a "/"?
		bool is_directory() const;
		
		/// Returns the directory part of the path, e.g. everything up to the last slash.
		Path directory() const;
		
		// Drop "." and remove ".." by dropping preceeding path elements.
		Path simplify() const;
		
		Path operator+(const Path & other) const;
		
		// Given a path of the form "/.../x" return "x".
		Path base_name() const;
		
		// Given a path of the form "/.../x/y", return "x".
		Path directory_name() const;
		
		// Given a path of the form "/.../x.y" return "y".
		std::string extension() const;
		
		bool operator==(const Path & other) const {return _value == other._value;}
		bool operator!=(const Path & other) const {return _value != other._value;}
		bool operator<(const Path & other) const {return _value < other._value;}
		bool operator<=(const Path & other) const {return _value <= other._value;}
		bool operator>(const Path & other) const {return _value > other._value;}
		bool operator>=(const Path & other) const {return _value >= other._value;}
		
	protected:
		std::string _value;
	};

	std::ostream & operator<<(std::ostream & output, const Path & path);
}
