#include "../includes/Server.hpp"

/**
* @todo _accept_connection
* Ajouter une limite de connection simultanee
*/
void Server::_accept_connection(fd_set & readfds)
{
	int		new_socket;

	if (FD_ISSET(_master_socket, &readfds))
	{

		log("Incoming connection");
		if ((new_socket = accept(_master_socket, (struct sockaddr *)&_address, &_addrlen)) < 0)
		{
			perror("accept error");
			_exit(1);
		}
		User new_user(new_socket);
		_users.push_back(new_user);
	}
}

void Server::_get_requests(fd_set & readfds, CommandManager & commandManager)
{
	char	buffer[1024];
	int		valread, sd;

	
	for (iterator it = _users.begin(); it != _users.end(); it++)
	{
		std::memset(&buffer, 0x00, 1024);
		sd = it->getFd();
		if (FD_ISSET(sd, &readfds))
		{
			if ((valread = read(sd, buffer, 1024)) == 0)
			{
				getpeername(sd, (struct sockaddr*)&_address, &_addrlen);
				close(sd);
				it->log("Disconnected");
				it->setStatus(User::DISCONNECT);
			}
			else if (it->isConnected())
			{
				buffer[valread] = '\0';
				commandManager.execCommand(&(*it), buffer);
			}
		}
	}
}

void Server::_run(fd_set & readfds)
{
	CommandManager commandManager;
	int activity;

	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(_master_socket, &readfds);
		_max_sd = _master_socket;
		_copy_fd(_users, readfds);
		activity = select(_max_sd + 1, &readfds, 0, 0, 0);
		if (activity < 0)
			perror("Select error");
		_accept_connection(readfds);
		_get_requests(readfds, commandManager);
		send_all();
		_remove_disconnect();
	}
}

/**
* @todo _remove_disconnect 
* Confirmer au client la deconnection
*/
void Server::_remove_disconnect()
{
	iterator it = _users.begin();

	while (it != _users.end())
	{
		if ((*it).getStatus() == User::DISCONNECT)
		{
			close((*it).getFd());
			_users.erase(it);
			it = _users.begin();
			continue;
		}
		it++;
	}
}

void Server::_copy_fd(std::vector<User> & clients, fd_set & readfds)
{
	typedef std::vector<User>::iterator iterator;
	int sd;

	for (iterator it = _users.begin(); it != _users.end(); it++)
	{
		sd = it->getFd();
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
		_exit(1);
	}
	if (setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&_opt, sizeof(_opt)) < 0)
	{
		perror("Error setsockopt: ");
		_exit(1);
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
	
	_server_password	= rhs._server_password;
	_master_socket 		= rhs._master_socket;
	_server_port 		= rhs._server_port;
	_new_socket			= rhs._new_socket;
	_activity			= rhs._activity;
	_addrlen			= rhs._addrlen;
	_address			= rhs._address;
	_max_sd				= rhs._max_sd;
	_users				= rhs._users;
	_opt				= rhs._opt;
	
	return *this;
}

Server::~Server(void)
{
	return ;
}

void Server::start(void)
{
	fd_set	readfds;
	if (bind(_master_socket, (struct  sockaddr *)& _address, sizeof(_address)) < 0)
	{
		perror ("Bind error");
		_exit(1);
	}
	_addrlen = sizeof(_address);
	log(std::string("Listening on port ") + std::to_string(_server_port));
	if (listen(_master_socket, 5) < 0)
	{
		perror("Listen error");
		_exit(1);
	}
	log("Waiting connections");
	_run(readfds);
	return;
}

void Server::send_all()
{
	for (iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->getBuffer().size())
			write(it->getFd(), it->getBuffer().c_str(), it->getBuffer().length());
		it->getBuffer().clear();
	}
}

const std::vector<User> & Server::getUsers() const { return (_users); }
const std::string & Server::getPass() const { return (_server_password); }


bool	Server::isUser(std::string const & name) const
{
	for (const_iterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it).getNick() == name)
			return true;
	}
	return false;
}


void	Server::kickAll(std::string const & reason)
{
    for (iterator it = _users.begin(); it != _users.end(); it++)
		it->kick(reason);
}

void	Server::shutdown(void) 
{
	log("\rShutdown IRC serv by SIGINT");
	kickAll("Sopping server");
	send_all();
	_remove_disconnect();
	close(_master_socket);
	_master_socket = -1;
	_users.clear();
	exit(0);
}

void Server::log(std::string const message) const
{
	time_t rawtime;
	struct tm * timeinfo;
	char timer [18];

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	if (strftime(timer,18, "[%d/%m:%R]", timeinfo) == 0)
	{
		std::cout << "Error Time" << std::endl;
		_exit(1);
	}
	std::cout << timer << "[Server][Info] " << message << std::endl;
}