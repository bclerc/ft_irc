#include "../includes/Server.hpp"

void Server::_copy_fd(std::vector<int> & clients, fd_set & readfds)
{
	typedef std::vector<int>::iterator iterator;
	int sd;

	for (iterator it = clients.begin(); it != clients.end(); it++)
	{
		sd = *it;
		if (sd > 0)
			FD_SET(sd, &readfds);
		if (sd > _max_sd)
			_max_sd = sd;
	}
}

Server::Server(int port, std::string const & name, std::string const & password) : 
			_server_port(port), _server_name(name), _server_password(password), _opt(0)
{

	if ((_master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Error socket: ");
		exit(1);
	}

	if (setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&_opt, sizeof(_opt)) < 0)
	{
		perror("Error setsockopt: ");
		exit(1);
	}

	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_server_port);

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
	(void)rhs;
	return *this;
}

Server::~Server(void)
{
	return ;
}

void Server::start(void)
{

	typedef std::vector<int>::iterator iterator;

	fd_set	readfds;
	char buffer[1025];
	int		activity;
	int		new_socket;
	int		valread;
	int		sd;

	log("Starting server on port " +  _server_port);
	if (bind(_master_socket, (struct  sockaddr *)&_address, sizeof(_address)) < 0)
	{
		perror ("Bind error");
		exit(1);
	}
	log("Listening ...");
	if (listen(_master_socket, 5) < 0)
	{
		perror("Listen error");
		exit(1);
	}
	log("Waiting for connections ...");
	_addrlen = sizeof(_address);
	char *message = "ECHO Daemon v1.0 \r\n";
	while (1)
	{
		std::memset(&buffer, 0x00, strlen(buffer));
		FD_ZERO(&readfds);
		FD_SET(_master_socket, &readfds);
		_max_sd = _master_socket;
		_copy_fd(_clients, readfds);
		activity = select(_max_sd + 1, &readfds, 0, 0, 0);
		if (activity < 0)
		{
			perror("Select error");
		}

		if (FD_ISSET(_master_socket, &readfds))
		{
			if ((new_socket = accept(_master_socket, (struct sockaddr *)&_address, &_addrlen)) < 0)
			{
				perror("accept error");
				exit(1);
			}
			std::cout << "[ " << new_socket << "] Connected" << std::endl;
			if (send (new_socket, message, strlen(message), 0) < 0)
				perror("send error");
			_clients.push_back(new_socket);
			log("New client added to list");	
		}

		for (iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			sd = *it;

			if (FD_ISSET(sd, &readfds))
			{
				if ((valread = read(sd, buffer, 1024)) == 0)
				{
					getpeername(sd, (struct sockaddr*)&_address, &_addrlen);
					std::cout << "[ " << sd << "] Disconnected" << std::endl;
					close(sd);
				}
				else
				{
						buffer[valread] = '\0';
					std::cout << "[ " << sd << "] (" << valread << ")" << buffer << std::endl;
				}
			}
		}
	}
	return;
}

void Server::log(std::string const message) const
{
	std::cout << _server_name << ": " << message << std::endl;
}