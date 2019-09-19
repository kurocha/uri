//
//  Platform.hpp
//  This Platform is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/9/2019.
//  Copyright, 2019, by Samuel Williams. All rights reserved.
//

#pragma once

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
}
