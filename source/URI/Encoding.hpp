//
//  Encoding.hpp
//  File file is part of the "URI" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <string>
#include <sstream>

namespace URI
{
	namespace Encoding
	{
		// Characters which can appear anywhere in an URI without any encoding.
		bool is_unreserved(unsigned char);
		
		// Characters which can appear within the query portion of a URI without any encoding.
		bool is_query_unreserved(unsigned char);
		
		// Characters which can appear in the path portion of a URI without any encoding.
		bool is_path_unreserved(unsigned char);
		
		// According to https://tools.ietf.org/html/rfc3986#section-3.3, we escape non-pchar using % encoding.
		std::string encode(const std::string & string, bool(*is_safe)(unsigned char) = is_unreserved);
		std::string decode(const std::string & string);
		
		template <typename IteratorT>
		std::string encode_query(IteratorT begin, IteratorT end)
		{
			std::stringstream buffer;
			
			if (begin != end) {
				buffer << encode(begin->first, is_query_unreserved) << '=' << encode(begin->second, is_query_unreserved);
				
				++begin;
			}
			
			while (begin != end) {
				buffer << '&' << encode(begin->first, is_query_unreserved) << '=' << encode(begin->second, is_query_unreserved);
				
				++begin;
			}
			
			return buffer.str();
		}
		
		template <typename IteratorT>
		std::string encode_path(IteratorT begin, IteratorT end)
		{
			std::stringstream buffer;
			
			if (begin != end) {
				buffer << encode(*begin, is_path_unreserved);
				
				++begin;
			}
			
			while (begin != end) {
				buffer << '/' << encode(*begin, is_path_unreserved);
				
				++begin;
			}
			
			return buffer.str();
		}
	};
}
