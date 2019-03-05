
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "3.0"

# Project Metadata

define_project "uri" do |project|
	project.title = "URI"
	
	project.summary = 'Proviers abstractions and parsers for dealing with URIs.'
	
	project.license = "MIT License"
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = "1.0.0"
end

# Build Targets

define_target 'uri-headers' do |target|
	# Because we need to compile the parsers (in a cache root) below, which need to access headers.
	target.provides "Headers/URI" do
		append header_search_paths target.package.path + 'source'
	end
end

define_target 'uri-library' do |target|
	target.depends "Language/C++14"
	
	target.depends "Headers/URI", public: true
	target.depends "Convert/Ragel"
	
	target.provides "Library/URI" do
		source_root = target.package.path + 'source'
		cache_prefix = environment[:build_prefix] + environment.checksum
		
		parsers = source_root.glob('URI/**/*Parser.rl')
		
		implementation_files = parsers.collect do |file|
			implementation_file = cache_prefix / (file.relative_path + '.cpp')
			convert source_file: file, destination_path: implementation_file
		end
		
		library_path = build static_library: "URI", source_files: (source_root.glob('URI/**/*.cpp') + implementation_files)
		
		append linkflags library_path
	end
end

define_target "uri-tests" do |target|
	target.depends "Language/C++14"
	
	target.depends "Library/UnitTest"
	target.depends "Library/URI"

	target.provides "Test/URI" do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: "URI", source_files: test_root.glob('URI/**/*.cpp'), arguments: arguments
	end
end

# Configurations

define_configuration "development" do |configuration|
	configuration[:source] = "https://github.com/kurocha"
	configuration.import "uri"
	
	# Provides all the build related infrastructure:
	configuration.require "platforms"
	configuration.require "build-files"
	
	# Provides unit testing infrastructure and generators:
	configuration.require "unit-test"
	
	# Provides some useful C++ generators:
	configuration.require "generate-cpp-class"
	configuration.require 'generate-project'
	configuration.require 'generate-travis'
end

define_configuration "uri" do |configuration|
	configuration.public!
	configuration.require "ragel"
end
