//
//  Path.cpp
//  File file is part of the "Uri" project and released under the MIT License.
//
//  Created by Samuel Williams on 13/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Path.hpp"

namespace URI
{
	// Pop a single path element:
	static void pop(std::string & path, char separator)
	{
		// path.size() returns one past the end, and we want to find the second to last slash.
		auto parent = path.rfind(separator, path.size()-1-1);

		if (parent != std::string::npos) {
			path.erase(parent+1, path.size());
		} else {
			path.clear();
		}
	}

	static void push(std::string & result, const std::string & path, std::size_t current, std::size_t next)
	{
		if (next == std::string::npos) {
			// There is no trailing separator, so we just copy everything:
			result.append(path.begin() + current, path.end());
		} else {
			// We increase next by 1 to include the trailing separator:
			result.append(path.begin() + current, path.begin() + next + 1);
		}
	}

	static std::string simplify(const std::string & path, char separator) {
		std::size_t current = 0, next = 0, size = 0, depth = 0;
		std::string result;

		// Avoid pointless memory allocations.
		result.reserve(path.size());

		while (true) {
			next = path.find(separator, current);

			// Determine if there are more path components:
			if (next == std::string::npos) {
				size = path.size() - current;
			} else {
				size = next - current;
			}
			
			// Look at the current path component:
			if (size == 1 && path[current] == '.') {
				// Ignore.
			} else if (size == 2 && path[current] == '.' && path[current+1] == '.') {
				if (depth > 0) { // If there are some non-empty path segments, we can pop one:
					pop(result, separator);

					depth -= 1;
				} else { // Nothing left to pop, so we can only append:
					push(result, path, current, next);
				}
			} else {
				push(result, path, current, next);

				if (size != 0) {
					// We can only pop off non-zero width segments:
					depth += 1;
				}
			}

			if (next == std::string::npos) break;

			current = next + 1;
		}

		return result;
	}

	bool Path::is_absolute() const {
		return !value.empty() && value.front() == SEPARATOR;
	}

	bool Path::is_directory() const {
		return !value.empty() && value.back() == SEPARATOR;
	}

	Path Path::directory() const {
		if (is_directory()) return *this;
		
		std::string copy = value;
		pop(copy, SEPARATOR);
		
		return copy;
	}

	Path Path::simplify() const {
		return URI::simplify(value, SEPARATOR);
	}
	
	Path Path::operator+(const Path & other) const
	{
		if (other.is_absolute()) return other;
		
		if (is_directory()) {
			return value + other.value;
		} else {
			return directory().value + other.value;
		}
	}
	
	// Path Path::operator+(const std::string & other) const
	// {
	// 	return value + other;
	// }
	
	Path Path::base_name() const
	{
		auto position = value.rfind(SEPARATOR);

		if (position == std::string::npos) {
			return value;
		} else {
			// We don't want to include the preceeding separator.
			position += 1;
			return value.substr(position, value.size() - position);
		}
	}
	
	Path Path::directory_name() const
	{
		auto position = value.rfind(SEPARATOR);

		if (position == std::string::npos) {
			return "";
		} else {
			auto start = value.rfind(SEPARATOR, position - 1);
			
			if (start == std::string::npos) {
				start = 0;
			} else {
				start += 1;
			}
			
			return value.substr(start, position - start);
		}
	}
	
	std::string Path::extension() const
	{
		if (value.empty()) return "";
		
		auto position = value.rfind(SEPARATOR);
		
		if (position == std::string::npos) {
			position = 0;
		} else {
			position += 1;
		}
		
		for (auto i = value.size() - 1; i > position; i -= 1) {
			if (value[i] == '.') {
				auto offset = i + 1;
				
				return value.substr(offset, value.size() - offset);
			}
		}
		
		return "";
	}
	
	std::ostream & operator<<(std::ostream & output, const Path & path) {
		return output << path.value;
	}
}
