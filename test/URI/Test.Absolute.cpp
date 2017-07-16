//
//  Test.Absolute.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Absolute.hpp>
#include <URI/Relative.hpp>

namespace URI
{
	UnitTest::Suite AbsoluteTestSuite {
		"URI::Absolute",
		
		{"it can add absolute uris",
			[](UnitTest::Examiner & examiner) {
				auto a1 = Absolute::parse("http://www.google.com");
				auto a2 = Absolute::parse("http://www.yahoo.com");
				
				auto result = a1 + a2;
				
				examiner.expect(result.generic()) == a2.generic();
			}
		},
		
		{"it can add absolute and relative uris",
			[](UnitTest::Examiner & examiner) {
				auto a1 = Absolute::parse("http://www.google.com");
				auto a2 = Relative::parse("/search?q=apples");
				
				auto result = a1 + a2;
				
				examiner.expect(result.generic().host) == "www.google.com";
				examiner.expect(result.path()) == "/search";
				examiner.expect(result.generic().query) == "q=apples";
			}
		},
		
		{"it can parse percent encoded uris",
			[](UnitTest::Examiner & examiner) {
				auto a1 = Absolute::parse("http://localhost/welcome%20home?hash=%23");
				
				examiner.expect(a1.generic().host) == "localhost";
				examiner.expect(a1.path()) == "/welcome home";
				examiner.expect(a1.generic().query) == "hash=%23";
			}
		},
	};
}
