//
//  File.hpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 20/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Generic.hpp"

namespace URI
{
	struct File : public Generic
	{
		// Convert a local path to a URI encoded path.
		File(const Path & path_) : Generic("file", "", "", "", path_, "", "") {}
	};
}
