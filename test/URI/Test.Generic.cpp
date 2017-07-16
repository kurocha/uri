//
//  Test.Generic.cpp
//  This file is part of the "Uri" project and released under the MIT License.
//
//  Created by Samuel Williams on 13/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Generic.hpp>

namespace URI
{
	UnitTest::Suite GenericTestSuite {
		"URI::Generic",
		
		{"it is absolute",
			[](UnitTest::Examiner & examiner) {
				Generic generic{"http", "", "www.google.com", "/foo/bar", "", "", ""};
				
				examiner << generic << " is absolute" << std::endl;
				examiner.check(generic.is_absolute());
			}
		},
		
		{"it is relative",
			[](UnitTest::Examiner & examiner) {
				Generic generic{"", "", "", "/foo/bar", "", "", ""};
				
				examiner << generic << " is relative" << std::endl;
				examiner.check(generic.is_relative());
			}
		},
		
		{"it can percent encode non-pchars",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(encode("foo bar")) == "foo%20bar";
			}
		},
		
		{"it can percent decode",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(decode("foo%20bar")) == "foo bar";
			}
		},
	};
}
