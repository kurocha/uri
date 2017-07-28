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
	Native<Platform::UNIX>::Native(const std::string & path, bool directory) : Generic("file", "", "", "", Encoding::encode_path(path, '/', directory), "", "")
	{
	}
	
	std::string Native<Platform::UNIX>::native_path(const URI::Generic & uri)
	{
		if (uri.scheme != "file") {
			throw std::invalid_argument("Cannot generate native path from non-file URI!");
		}
		
		return Encoding::decode_path(uri.path.value, '/');
	}
	
	// URI::File Native<Platform::UNIX>::Native(const std::string & path, bool directory)
	// {
	// }
	// 
	// std::string Native<Platform::UNIX>::path(const URI::Generic & uri)
	// {
	// }
}
