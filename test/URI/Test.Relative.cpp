//
//  Test.Relative.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Relative.hpp>

namespace URI
{
	UnitTest::Suite RelativeTestSuite {
		"URI::Relative",
		
		{"it can add two absolute paths",
			[](UnitTest::Examiner & examiner) {
				Relative r1{"/foo/bar"}, r2{"/foo/baz"};
				
				auto result = r1 + r2;
				
				examiner.expect(result.path()) == "/foo/baz";
			}
		},
		
		{"it can add absolute and relative paths",
			[](UnitTest::Examiner & examiner) {
				Relative r1{"/foo/bar"}, r2{"baz"};
				
				auto result = r1 + r2;
				
				examiner.expect(result.path()) == "/foo/baz";
			}
		},
		
		{"it can add two relative paths",
			[](UnitTest::Examiner & examiner) {
				Relative r1{"foo/bar"}, r2{"baz"};
				
				auto result = r1 + r2;
				
				examiner.expect(result.path()) == "foo/baz";
			}
		},
		
		{"it can parse percent encoded uris",
			[](UnitTest::Examiner & examiner) {
				auto relative = Relative::parse("/welcome%20home?hash=%23");
				
				examiner.expect(relative.path()) == "/welcome home";
				examiner.expect(relative.query()) == "hash=%23";
			}
		},
	};
}
