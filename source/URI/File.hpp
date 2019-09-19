//
//  File.hpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Generic.hpp"
#include "Platform.hpp"

namespace URI
{
	// Native URIs represent paths to local files. They must use the `file:` scheme.
	// The normal pattern is to construct them using generic URIs, which will generate the correct `native_path` strings.
	template <Platform PLATFORM = Platform::DEFAULT>
	struct Native : public Generic
	{
		// Creates a URI with the file scheme, and the given native path.
		Native(const std::string & native_path, bool directory = false);
	};
	
	using File = Native<>;
	
	std::string native_path(const Generic & generic);
	
	template <Platform PLATFORM = Platform::DEFAULT>
	std::string native_path(const Path & path);
}
