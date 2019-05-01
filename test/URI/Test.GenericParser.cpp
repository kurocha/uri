//
//  Test.GenericParser.cpp
//  This file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 15/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/GenericParser.hpp>

namespace URI
{
	UnitTest::Suite GenericParserTestSuite {
		"URI::GenericParser",
		
		{"it can parse absolute url",
			[](UnitTest::Examiner & examiner) {
				std::string text = "http://foo:bar@www.oriontransfer.co.nz/welcome/index";
				auto generic = Generic(text);
				
				examiner.expect(generic.scheme) == "http";
				examiner.expect(generic.userinfo) == "foo:bar";
				examiner.expect(generic.port) == "";
				examiner.expect(generic.host) == "www.oriontransfer.co.nz";
				examiner.expect(generic.path) == "/welcome/index";
				examiner.expect(generic.query) == "";
				examiner.expect(generic.fragment) == "";
				
				std::stringstream buffer;
				buffer << generic;
				examiner.expect(buffer.str()) == text;
			}
		},
		
		{"it can parse absolute url with ipv4 address",
			[](UnitTest::Examiner & examiner) {
				std::string text = "http://127.0.0.1:8080";
				auto generic = Generic(text);
				
				examiner.expect(generic.scheme) == "http";
				examiner.expect(generic.userinfo) == "";
				examiner.expect(generic.port) == "8080";
				examiner.expect(generic.host) == "127.0.0.1";
				examiner.expect(generic.path) == "";
				examiner.expect(generic.query) == "";
				examiner.expect(generic.fragment) == "";
				
				std::stringstream buffer;
				buffer << generic;
				examiner.expect(buffer.str()) == text;
			}
		},
		
		{"it can parse absolute url with ipv6 address",
			[](UnitTest::Examiner & examiner) {
				std::string text = "http://[::1]:8080";
				auto generic = Generic(text);
				
				examiner.expect(generic.scheme) == "http";
				examiner.expect(generic.userinfo) == "";
				examiner.expect(generic.port) == "8080";
				examiner.expect(generic.host) == "[::1]";
				examiner.expect(generic.path) == "";
				examiner.expect(generic.query) == "";
				examiner.expect(generic.fragment) == "";
				
				std::stringstream buffer;
				buffer << generic;
				examiner.expect(buffer.str()) == text;
			}
		},
		
		{"it can parse relative url",
			[](UnitTest::Examiner & examiner) {
				std::string text = "welcome/index";
				auto generic = Generic(text);
				
				examiner.expect(generic.scheme) == "";
				examiner.expect(generic.userinfo) == "";
				examiner.expect(generic.port) == "";
				examiner.expect(generic.host) == "";
				examiner.expect(generic.path) == "welcome/index";
				examiner.expect(generic.query) == "";
				examiner.expect(generic.fragment) == "";
				
				std::stringstream buffer;
				buffer << generic;
				examiner.expect(buffer.str()) == text;
			}
		},
		
		{"it can parse relative url with query & fragment",
			[](UnitTest::Examiner & examiner) {
				std::string text = "welcome/index?fruit[]=apple&fruit[]=orange#first";
				auto generic = Generic(text);
				
				examiner.expect(generic.scheme) == "";
				examiner.expect(generic.userinfo) == "";
				examiner.expect(generic.port) == "";
				examiner.expect(generic.host) == "";
				examiner.expect(generic.path) == "welcome/index";
				examiner.expect(generic.query) == "fruit[]=apple&fruit[]=orange";
				examiner.expect(generic.fragment) == "first";
				
				std::stringstream buffer;
				buffer << generic;
				examiner.expect(buffer.str()) == text;
			}
		},
		
		{"it can parse relative url with host",
			[](UnitTest::Examiner & examiner) {
				std::string text = "//welcome/index";
				auto generic = Generic(text);
				
				examiner.expect(generic.scheme) == "";
				examiner.expect(generic.userinfo) == "";
				examiner.expect(generic.port) == "";
				examiner.expect(generic.host) == "welcome";
				examiner.expect(generic.path) == "/index";
				examiner.expect(generic.query) == "";
				examiner.expect(generic.fragment) == "";
				
				std::stringstream buffer;
				buffer << generic;
				examiner.expect(buffer.str()) == text;
			}
		},
		
		{"it can parse curly brackets",
			[](UnitTest::Examiner & examiner) {
				std::string text = "render?clip={{0,0},{100,100}}";
				auto generic = Generic(text);
				
				examiner.expect(generic.path) == "render";
				examiner.expect(generic.query) == "clip={{0,0},{100,100}}";
			}
		},
		
		{"it can decode uri parameters",
			[](UnitTest::Examiner & examiner){
				std::string text = "http://localhost:10802/render?crop=1127%2C810%2C946%2C946&e_uri=%2Fdata%2Frenderraum%2Fdata%2Fstandard_size_mhoodie_front_mens-front.tfb&texture_uri=http%3A%2F%2Fredbubble.s3.amazonaws.com%2Fdata%2Fstorage%2Fbase%2F2009%2F10%2F10%2F18%2F6435506.png%3FAWSAccessKeyId%3DBJPIUAQAW5SDIKAKQKUT%26Expires%3D1556688111%26Signature%3DL0XyrRYl9R1dqh8jbMT5Fmvz8Ow%253D";
				
				auto generic = Generic(text);
				
				examiner.expect(generic.path) == "/render";
				
				auto named_values = generic.query.to_map();
				
				examiner.expect(named_values.find("texture_uri")->second) == "http://redbubble.s3.amazonaws.com/data/storage/base/2009/10/10/18/6435506.png?AWSAccessKeyId=BJPIUAQAW5SDIKAKQKUT&Expires=1556688111&Signature=L0XyrRYl9R1dqh8jbMT5Fmvz8Ow%3D";
			}
		},
		
		// The UTF8 character needs to be encoded for this test to pass.
		// {"it can parse unicode",
		// 	[](UnitTest::Examiner & examiner) {
		// 		std::string text = "//welcome/index?utf8=✓";
		// 		auto generic = Generic(text);
		// 		
		// 		examiner.expect(generic.query) == "utf8=✓";
		// 	}
		// }
	};
}
