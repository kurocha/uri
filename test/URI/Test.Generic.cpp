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
		
		{"it can add absolute uris",
			[](UnitTest::Examiner & examiner) {
				auto a1 = Generic::parse("http://www.google.com");
				auto a2 = Generic::parse("http://www.yahoo.com");
				
				auto result = a1 + a2;
				
				examiner.expect(result) == a2;
			}
		},
		
		{"it can add absolute and relative uris",
			[](UnitTest::Examiner & examiner) {
				auto a1 = Generic::parse("http://www.google.com");
				auto a2 = Generic::parse("/search?q=apples");
				
				auto result = a1 + a2;
				
				examiner.expect(result.host) == "www.google.com";
				examiner.expect(result.path) == "/search";
				examiner.expect(result.query) == "q=apples";
			}
		},
		
		{"it can parse percent encoded uris",
			[](UnitTest::Examiner & examiner) {
				auto a1 = Generic::parse("http://localhost/welcome%20home?hash=%23");
				
				examiner.expect(a1.host) == "localhost";
				examiner.expect(a1.path) == "/welcome%20home";
				examiner.expect(a1.query) == "hash=%23";
			}
		},
		
		{"it can add two absolute paths",
			[](UnitTest::Examiner & examiner) {
				auto r1 = Generic::parse("/foo/bar"), r2 = Generic::parse("/foo/baz");
				
				auto result = r1 + r2;
				
				examiner.expect(result.path) == "/foo/baz";
			}
		},
		
		{"it can add absolute and relative paths",
			[](UnitTest::Examiner & examiner) {
				auto r1 = Generic::parse("/foo/bar"), r2 = Generic::parse("baz");
				
				auto result = r1 + r2;
				
				examiner.expect(result.path) == "/foo/baz";
			}
		},
		
		{"it can add two relative paths",
			[](UnitTest::Examiner & examiner) {
				auto r1 = Generic::parse("foo/bar"), r2 = Generic::parse("baz");
				
				auto result = r1 + r2;
				
				examiner.expect(result.path) == "foo/baz";
			}
		},
		
		{"it can parse percent encoded uris",
			[](UnitTest::Examiner & examiner) {
				auto relative = Generic::parse("/welcome%20home?hash=%23");
				
				examiner.expect(relative.path) == "/welcome%20home";
				examiner.expect(relative.query) == "hash=%23";
			}
		},
	};
}
