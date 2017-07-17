//
//  Test.Encoding.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Encoding.hpp>

#include <map>

namespace URI
{
	UnitTest::Suite EncodingTestSuite {
		"URI::Encoding",
		
		{"it can percent encode non-pchars",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(Encoding::encode("foo bar")) == "foo%20bar";
			}
		},
		
		{"it can percent decode",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(Encoding::decode("foo%20bar")) == "foo bar";
			}
		},
		
		{"it can encode query",
			[](UnitTest::Examiner & examiner){
				std::map<std::string, std::string> arguments;
				arguments["x[]"] = "http://www.google.com/search?q=lucid";
				
				auto query = Encoding::encode_query(arguments.begin(), arguments.end());
				
				examiner.expect(query) == "x[]=http://www.google.com/search%3Fq%3Dlucid";
			}
		},
		
		{"it can encode path",
			[](UnitTest::Examiner & examiner){
				std::vector<std::string> entries = {"blog", "2017", "Apples/oranges & the path to fruit salad!"};
				
				auto path = Encoding::encode_path(entries.begin(), entries.end());
				
				examiner.expect(path) == "blog/2017/Apples%2Foranges%20&%20the%20path%20to%20fruit%20salad!";
			}
		},
	};
}
