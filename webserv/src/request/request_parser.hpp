#ifndef __FT_REQUEST_PARSER_H__
#define __FT_REQUEST_PARSER_H__

#include "body.hpp"
#include "header.hpp"
#include "startline.hpp"
#include <map>
#include <string>
#include <vector>

struct RequestParser
{
	static void startlineParser(Startline &startline, const std::string &str);
	static void headerParser(Header &header, std::map<std::string, std::string> &headerbuf,
													 const std::string &method);
	static void fillHeaderBuffer(std::map<std::string, std::string> &headerbuf,
															 const std::string &str,
															 const size_t headerbufSize);
	static void bodyParser(Body& body, std::vector<char> &bodyOctets, Header& header);

private:
	static std::vector<std::string> methodTokenSet;
	static const size_t maxHeaderSize = 8 * 1024;
	static const size_t maxHeaderFieldSize = 30 * 1024;

	static std::vector<std::string> initMethodTokenSet(void);
	/**
	 * startline parser util
	 */
	static void startlineMethodParser(std::string &method, const std::string &token);
	static void startlineURIParser(std::string &uri, const std::string &token, const std::string &method);
	static void startlineHTTPVersionParser(std::string &httpVersion, const std::string &token);
	// static bool validateHeaderValue(Header &header);

	/**
	 * header parser util
	 */
	static bool checkHeaderFieldnameHasSpace(const std::string &fieldname);
	static bool checkHeaderFieldContain(const std::map<std::string, std::string> &headerbuf,
																			const std::string str);
	static void headerValueParser(std::vector<FieldValue> &fieldvalue, const std::string &headerValue);
	static void headerValueDescriptionParser(std::map<std::string, std::string> &descriptions,
															std::vector<std::string> &descriptionsTokenSet);
	static int chunkedBodyParser(Body& body, std::vector<char>& bodyOctets);
	static int contentLengthBodyParser(Body& body, std::vector<char>& bodyOctets, Header& header);


	/**
	 * uri parser util
	 */
	static bool checkURIOriginForm(std::string &uri, const std::string &token);
	static bool checkURIAbsoluteForm(std::string &uri, const std::string &token);
	static bool checkURIAuthorityForm(std::string &uri, const std::string &token, const std::string &method);
	static bool checkURIAsteriskForm(std::string &uri, const std::string &token, const std::string &method);

	static size_t findToken(const std::string &token, const std::vector<std::string> &tokenset);
	static std::vector<std::string> splitStr(const std::string &token, const char *delimiter);
	static std::string &trimStr(std::string &target, const std::string &charset);
	static std::string tolowerStr(const char* str);
	static char* vecToCstr(const std::vector<char>& vec, size_t size);
	static std::vector<char> cstrToVec(const char* cstr, size_t size);
};

#endif