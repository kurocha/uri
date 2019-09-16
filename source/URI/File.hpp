//
//  File.hpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Generic.hpp"

namespace URI
{
	enum class Platform : std::uint8_t {
		UNIX = '/',
		WINDOWS = '\\',
		
#if defined(_WIN32)
		DEFAULT = WINDOWS,
#else
		DEFAULT = UNIX,
#endif
	};
	
	template <Platform PLATFORM = Platform::DEFAULT>
	struct Native : public Generic
	{
		using Generic::Generic;
		
		// Copy the URI, but throws an exception if the other URI is not using the "file" scheme.
		Native(const Generic & other);
		
		// Creates a URI with the file scheme, and the given native path.
		Native(const std::string & native_path, bool directory = false);
		
		std::string native_path() const;
	};
	
	using File = Native<>;
}
