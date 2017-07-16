%%{
	# A URI parser grammer.
	# Based on https://tools.ietf.org/html/rfc3986

	machine RFC3986;
	alphtype unsigned char;
	
	percent_encoded = "%" xdigit xdigit;
	unreserved = alnum | "-" | "." | "_" | "~";
	subcomponent_delimiters = "!" | "$" | "&" | "'" | "(" | ")" | "*" | "+" | "," | ";" | "=";
	general_delimiters = ":" | "/" | "?" | "#" | "[" | "]" | "@";
	
	# As discussed here, '[' and ']' are commonly used in the query part of a URI, along with '|', ':' and '@'.
	# https://stackoverflow.com/questions/11490326/is-array-syntax-using-square-brackets-in-url-query-strings-valid
	# Thus, we allow this implementation to parse those characters as if they were unreserved.
	unsafe = ":" | "@" | '[' | ']' | '|';
	
	decimal_octet =
		digit | # 0-9
		0x31..0x39 digit | # 10-99
		"1" digit{2} | # 100-199
		"2" 0x30..0x34 digit | # 200-249
		"25" 0x30..0x34; # 250-255

	address_ipv4 = decimal_octet "." decimal_octet "." decimal_octet "." decimal_octet;
	
	h16 = xdigit{1,4};
	ls32 = (h16 ":" h16) | address_ipv4;
	
	address_ipv6 =
		                          (h16 ":"){6} ls32 |
		                     "::" (h16 ":"){5} ls32 |
		(              h16)? "::" (h16 ":"){4} ls32 |
		((h16 ":"){,1} h16)? "::" (h16 ":"){3} ls32 |
		((h16 ":"){,2} h16)? "::" (h16 ":"){2} ls32 |
		((h16 ":"){,3} h16)? "::"  h16 ":"     ls32 |
		((h16 ":"){,4} h16)? "::"              ls32 |
		((h16 ":"){,5} h16)? "::"               h16 |
		((h16 ":"){,6} h16)? "::";
	
	address_future = "v" xdigit{1} "." (unreserved | subcomponent_delimiters | ":"){1};
	address_literal = "[" (address_ipv6 | address_future) "]";
	
	reserved = general_delimiters | subcomponent_delimiters;
	
	pchar = unreserved | percent_encoded | subcomponent_delimiters | unsafe;
	
	query = (pchar | "/" | "?")* >mark %query;
	fragment = (pchar | "/" | "?")* >mark %fragment;

	segment = pchar*;
	segment_nz = pchar+;
	
	# segment_nz_nc = (unreserved | percent_encoded | subcomponent_delimiters | "@")+;
	segment_nz_nc = (pchar - ":")+;

	path_abempty = (("/" segment)*) >mark %path;
	path_absolute = ("/" (segment_nz ("/" segment)*)?) >mark %path;
	path_noscheme = (segment_nz_nc ("/" segment)*) >mark %path;
	path_rootless = (segment_nz ("/" segment)*) >mark %path;
	path_empty = "";

	regular_name = (unreserved | percent_encoded | subcomponent_delimiters)*;

	port = digit* >mark %port;
	host = (address_literal | address_ipv4 | regular_name) >mark %host;
	userinfo = (unreserved | percent_encoded | subcomponent_delimiters | ":")* >mark %userinfo;
	authority = (userinfo "@")? host (":" port)?;

	scheme = alpha >mark (alpha | digit | "+" | "-" | ".")* %scheme;

	# path = (path_abempty | path_absolute | path_noscheme | path_rootless | path_empty) >mark %path;

	relative_part =
		"//" authority path_abempty |
		path_absolute |
		path_noscheme |
		path_empty;

	hierarchy_part =
		"//" authority path_abempty |
		path_absolute |
		path_rootless |
		path_empty;

	relative = relative_part ("?" query)? ("#" fragment)?;
	absolute = scheme ":" hierarchy_part ("?" query)? ("#" fragment)?;
	
	uri = relative | absolute @err(error);
}%%