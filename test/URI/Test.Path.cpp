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
				examiner << p1 << " is absolute";
				examiner.check(p1.is_absolute());
				
				examiner << p2 << " is relative";
				examiner.check(!p2.is_absolute());
				
				examiner << p2 << " is a directory";
				examiner.check(p2.is_directory());
				
				examiner << p3 << " is not a directory";
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
	};
}
