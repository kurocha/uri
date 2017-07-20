# URI

Abstractions for handling URIs. Provides RFC-derived parsers and encoders.

[![Build Status](https://travis-ci.org/kurocha/uri.svg?branch=master)](https://travis-ci.org/kurocha/uri)

## Setup

The build tool `teapot` needs to be installed (which requires [Ruby][2]):

	$ gem install teapot

[2]: http://www.ruby-lang.org/en/downloads/

### Install Dependencies

To fetch project dependencies, run the following:

	$ cd uri
	$ teapot fetch

### Validate Behaviour

The project can be checked by running unit tests:

	$ cd uri
	$ teapot Test/URI

## Usage

To parse a URI:

```c++
auto uri = URI::Generic("http://localhost/index.html?foo=bar");

uri.scheme == "http";
uri.host == "localhost";
uri.path == "/index.html";
uri.query == "foo=bar";
uri.fragment == "";
```

### Query Parameters

You can parse a query string into a `std::multimap`:

```c++
auto arguments = uri.query.to_map();
auto foo = arguments.find("foo");

foo->second == "bar";
```

It will correctly handle URL decoding.

You can convert any set of iterators of `std::pair` to a query string:

```c++
std::map<std::string, std::string> arguments = {...};
auto query = Query(arguments.begin(), arguments.end());
```

This will correctly handle URL encoding.

### Path Components

You can parse a path into a `std::vector`:

```c++
auto components = uri.path.to_vector();
```

A path which begins in a `/` will have `components[0] == ""` and the vice versa if it ends with a `/`.

You can convert a list of names back into a path:

```c++
std::vector components = {"S p a c e s", "s/l/a/s/h/e/s"};
auto path = Path(components.begin(), components.end());
```

It will correctly encode characters.

### International Resource Identifiers

IRIs as defined in [RFC3987](rfc) are not currently supported.

[rfc3987]: https://www.ietf.org/rfc/rfc3987.txt

## Contributing

1. Fork it.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.

## License

Released under the MIT license.

Copyright, 2017, by Samuel Williams. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
