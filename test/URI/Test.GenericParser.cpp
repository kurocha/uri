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
				auto generic = Generic::parse(text);
				
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
				auto generic = Generic::parse(text);
				
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
				auto generic = Generic::parse(text);
				
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
				auto generic = Generic::parse(text);
				
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
				auto generic = Generic::parse(text);
				
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
				auto generic = Generic::parse(text);
				
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
	};
}
