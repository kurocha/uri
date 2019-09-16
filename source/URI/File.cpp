//
//  File.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "File.hpp"

namespace URI
{
	template <Platform PLATFORM>
	Native<PLATFORM>::Native(const Generic & other) : Generic(other)
	{
		if (this->scheme != "file") {
			throw std::invalid_argument("non-file URI!");
		}
	}
	
	template<>
	Native<Platform::UNIX>::Native(const std::string & native_path, bool directory) : Generic("file", "", "", "", Encoding::encode_path(native_path, '/', directory), "", "")
	{
	}
	
	template<>
	std::string Native<Platform::UNIX>::native_path() const
	{
		if (this->scheme != "file") {
			throw std::invalid_argument("Cannot generate native path from non-file URI!");
		}
		
		return Encoding::decode_path(this->path.value, '/');
	}
	
	template<>
	Native<Platform::WINDOWS>::Native(const std::string & native_path, bool directory) : Generic("file", "", "", "", Encoding::encode_path(native_path, '\\', directory), "", "")
	{
	}
	
	template<>
	std::string Native<Platform::WINDOWS>::native_path() const
	{
		if (this->scheme != "file") {
			throw std::invalid_argument("Cannot generate native path from non-file URI!");
		}
		
		return Encoding::decode_path(this->path.value, '\\');
	}
	
	template struct Native<Platform::UNIX>;
	template struct Native<Platform::WINDOWS>;
}
