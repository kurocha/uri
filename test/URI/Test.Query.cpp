//
//  Test.Query.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Generic.hpp>
#include <URI/Query.hpp>

namespace URI
{
	UnitTest::Suite QueryTestSuite {
		"URI::Query",
		
		{"it can join two queries",
			[](UnitTest::Examiner & examiner){
				Query q1 = "foo=bar", q2 = "bob=dole";
				
				examiner.expect(q1+q2) == "foo=bar&bob=dole";
			}
		},
		
		{"it can decode arguments",
			[](UnitTest::Examiner & examiner){
				std::string remote = "http://s3.fakeamazon.com/data/floop.jpg?AccessKey[]=BLEEPBLOOP&SignatureHcM%2D1Ius%3D";
				std::string target = "/render?remote_uri=" + Encoding::encode(remote);
				
				auto target_uri = URI::Generic::parse(target);

				auto arguments = target_uri.query.to_map();
				auto remote_uri = arguments.find("remote_uri");
				
				examiner.check(remote_uri != arguments.end());
				examiner.expect(remote_uri->second) == remote;
			}
		},
	};
}
