//
//  Test.File.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 20/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/File.hpp>

namespace URI
{
	UnitTest::Suite FileTestSuite {
		"URI::File",
		
		{"it can construct file url from path",
			[](UnitTest::Examiner & examiner) {
				URI::File uri("foo/bar");
				
				examiner.expect(uri.scheme) == "file";
				examiner.expect(uri.path) == "foo/bar";
			}
		},
	};
}
