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
	template<>
	Native<Platform::UNIX>::Native(const std::string & native_path, bool directory) : Generic("file", "", "", "", Encoding::encode_path(native_path, '/', directory), "", "")
	{
	}
	
	template<>
	Native<Platform::WINDOWS>::Native(const std::string & native_path, bool directory) : Generic("file", "", "", "", Encoding::encode_path(native_path, '\\', directory), "", "")
	{
	}
	
	template<>
	std::string native_path<Platform::UNIX>(const Path & path)
	{
		return Encoding::decode_path(path.value, '/');
	}
	
	template<>
	std::string native_path<Platform::WINDOWS>(const Path & path)
	{
		return Encoding::decode_path(path.value, '\\');
	}
	
	std::string native_path(const Generic & generic)
	{
		if (generic.scheme != "file") {
			throw std::invalid_argument("Cannot generate native path from non-file URI!");
		}
		
		return native_path(generic.path);
	}
}
