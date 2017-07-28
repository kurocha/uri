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
	struct Native {};
	
	template <>
	struct Native<Platform::UNIX> : public URI::Generic
	{
		Native(const std::string & path, bool directory = false);
		
		static std::string native_path(const URI::Generic & uri);
	};
	
	// template <>
	// struct Native<Platform::WINDOWS> : public URI::Generic
	// {
	// 	Native(const std::string & path, bool directory);
	// 	
	// 	static std::string native_path(const URI::Generic & uri);
	// };
	
	using File = Native<>;
}
