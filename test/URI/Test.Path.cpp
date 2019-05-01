//
//  Test.Path.cpp
//  This file is part of the "Uri" project and released under the MIT License.
//
//  Created by Samuel Williams on 13/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <URI/Path.hpp>

namespace URI
{
	Path p1("/apples/oranges"), p2("grapefruit/"), p3("bananna/peach"), p4("files/image.jpeg"), p5("bob"), p6("/dole");
	
	UnitTest::Suite PathTestSuite {
		"URI::Path",
		
		{"it is relative/absolute/directory",
			[](UnitTest::Examiner & examiner) {
				examiner << p1 << " is absolute" << std::endl;
				examiner.check(p1.is_absolute());
				
				examiner << p2 << " is relative" << std::endl;
				examiner.check(!p2.is_absolute());
				
				examiner << p2 << " is a directory" << std::endl;
				examiner.check(p2.is_directory());
				
				examiner << p3 << " is not a directory" << std::endl;
				examiner.check(!p3.is_directory());
			}
		},

		{"it has path base name and extension",
			[](UnitTest::Examiner & examiner) {
				auto path = Path("files/image.jpeg");
				examiner.expect(path.base_name()) == "image.jpeg";
				examiner.expect(path.extension()) == "jpeg";

				auto base = Path("bob/");
				examiner.expect(base + path) == "bob/files/image.jpeg";
				
				examiner.expect(Path("").extension()) == "";
				examiner.expect(Path("/").extension()) == "";
				examiner.expect(Path("foo/").extension()) == "";
				
				examiner.expect(Path("foo.txt").extension()) == "txt";
				examiner.expect(Path("foo/bar.txt").extension()) == "txt";
				
				examiner.expect(Path("").base_name()) == "";
				examiner.expect(Path("/").base_name()) == "";
				examiner.expect(Path("foo/").base_name()) == "";
				
				examiner.expect(Path("foo.txt").base_name()) == "foo.txt";
				examiner.expect(Path("foo/bar.txt").base_name()) == "bar.txt";
			}
		},
		
		{"it can compute relative path",
			[](UnitTest::Examiner & examiner) {
				auto base = Path("/apples/oranges/");
				
				Path relative = base + Path("../john.png");
				examiner.expect(relative.simplify()) == "/apples/john.png";
			}
		},
		
		{"it can extract decoded elements of directory",
			[](UnitTest::Examiner & examiner){
				auto base = Path("/apples%20oranges/");
				
				auto components = base.to_vector();
				
				examiner.expect(components.size()) == 3;
				examiner.expect(components[0]) == "";
				examiner.expect(components[1]) == "apples oranges";
				examiner.expect(components[2]) == "";
			}
		},
		
		{"it can extract decoded elements of basename",
			[](UnitTest::Examiner & examiner){
				auto base = Path("/apples%2Foranges");
				
				auto components = base.to_vector();
				
				examiner.expect(components.size()) == 2;
				examiner.expect(components[0]) == "";
				examiner.expect(components[1]) == "apples/oranges";
			}
		},
		
		{"it can extract decoded elements of empty path",
			[](UnitTest::Examiner & examiner){
				auto base = Path("");
				
				auto components = base.to_vector();
				
				examiner.expect(components.size()) == 1;
				examiner.expect(components[0]) == "";
			}
		},
	};
}
