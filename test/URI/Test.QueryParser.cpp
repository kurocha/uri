//
//  Test.QueryParser.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/QueryParser.hpp>

#include <typeinfo>

namespace URI
{
	UnitTest::Suite QueryParserTestSuite {
		"URI::QueryParser",
		
		{"it can parse empty query",
			[](UnitTest::Examiner & examiner) {
				QueryParser::NamedValues named_values;
				unsigned char buffer[] = "x=10&y=20";
				QueryParser::parse(std::begin(buffer), std::end(buffer)-1, named_values);
				
				examiner.expect(named_values.size()) == 2;
				examiner.expect(named_values.find("x")->second) == "10";
				examiner.expect(named_values.find("y")->second) == "20";
			}
		},
	};
}
