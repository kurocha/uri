//
//  Test.Query.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Query.hpp>

namespace URI
{
	UnitTest::Suite QueryTestSuite {
		"URI::Query",
		
		{"it can join two queries",
			[](UnitTest::Examiner & examiner) {
				Query q1 = "foo=bar", q2 = "bob=dole";
				
				examiner.expect(q1+q2) == "foo=bar&bob=dole";
			}
		},
	};
}
