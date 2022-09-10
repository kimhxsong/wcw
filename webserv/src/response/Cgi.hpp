#ifndef CGI_HPP
#define CGI_HPP

#include <sstream>
#include <string>
#include <unistd.h>

class Response;

class Cgi
{
public:
	bool isCgi;
	pid_t pid;
	int fd[2];

public:
	Cgi();
	Cgi(const Cgi &other);
	~Cgi();

	operator bool() const;
	
	bool fail();

	template<class Request, class Config, class Location>
	int run(Request &req, Config &config, Location &location, int clientFd);
	template<class Request, class Config, class Location>
	char **generateMetaVariables(Request &req, Config &config, Location &location, int clientFd);

	int parseCgiResponse(Response &res);
	int parseStatusHeader(std::stringstream &ss);
	size_t parseContentLength(std::stringstream &ss);
};

#endif // !CGI_HPP
