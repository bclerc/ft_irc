#include "../includes/Server.hpp"

Server::Server(int port, std::string const & name, std::string const & password) : 
			_server_port(port), _server_name(name), _server_password(password)
{
	
	return ;
}

Server::Server(void)
{
	return ;
}

Server::Server(Server & cpy)
{
	*this = cpy;
	return ;
}

Server & Server::operator=(Server const & rhs)
{
	return *this;
}

Server::~Server(void)
{
	return ;
}

void Server::start(void) const
{
	std::cout << "Starting server with port " << _server_port << std::endl;
	return;
}