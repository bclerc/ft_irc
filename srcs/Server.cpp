#include "../includes/Server.hpp"

void Server::_accept_connection(fd_set & readfds)
{
	int		new_socket;

	if (FD_ISSET(_master_socket, &readfds))
	{
		log("Incoming connection");
		if ((new_socket = accept(_master_socket, (struct sockaddr *)&_address, &_addrlen)) < 0)
		{
			std::cout << "accept error" << std::endl;
			server.shutdown();
		}
		_users.push_back(new User(new_socket));
		if (isFull())
			_users.back()->kick();
	}
}

void Server::_get_requests(fd_set & readfds, CommandManager & commandManager)
{
	char	buffer[1024];
	int		valread, sd;

	
	for (iterator it = _users.begin(); it != _users.end(); it++)
	{
		std::memset(&buffer, 0x00, 1024);
		sd = (*it)->getFd();
		if (FD_ISSET(sd, &readfds))
		{
			if ((valread = read(sd, buffer, 1024)) == 0)
			{
				getpeername(sd, (struct sockaddr*)&_address, &_addrlen);
				close(sd);
				(*it)->log("Disconnected");
				(*it)->setStatus(User::DISCONNECT);
			}
			else if ((*it)->isConnected())
			{
				buffer[valread] = 0;
				(*it)->receive_buffer += buffer;
				commandManager.execCommand(*it);
			}
		}
	}
}

void Server::_run(fd_set & readfds)
{
	CommandManager commandManager;
	int activity;

	while (_status)
	{
		FD_ZERO(&readfds);
		FD_SET(_master_socket, &readfds);
		_max_sd = _master_socket;
		_copy_fd(readfds);
		activity = select(_max_sd + 1, &readfds, 0, 0, 0);
		if (activity < 0)
			perror("Select error");
		_accept_connection(readfds);
		_get_requests(readfds, commandManager);
		send_all();
		_remove_disconnect();
	}
}

void Server::_remove_disconnect()
{
	iterator it = _users.begin();

	while (it != _users.end())
	{
		if ((*it)->getStatus() == User::DISCONNECT)
		{
			(*it)->log("Disconnected");
			close((*it)->getFd());
			_users.erase(it);
			delete *it;
			it = _users.begin();
			continue;
		}
		it++;
	}
}

void Server::_copy_fd(fd_set & readfds)
{
	int sd;

	for (iterator it = _users.begin(); it != _users.end(); it++)
	{
		sd = (*it)->getFd();
		if (sd > 0)
			FD_SET(sd, &readfds);
		if (sd > _max_sd)
			_max_sd = sd;
	}
}

Server::Server(int port, std::string const & name, std::string const & password, int const & slots) 
			: _status(1),_server_port(port), _server_name(name), _server_password(password), _opt(0), _slots(slots)
{

	if ((_master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "Socket unexpected error" << std::endl;
		return ;
	}
	if (setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&_opt, sizeof(_opt)) < 0)
	{
		std::cout << "setsockopt unexpected error" << std::endl;
		return ;
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
	_status				= rhs._status;
	_users				= rhs._users;
	_slots				= rhs._slots;
	_opt				= rhs._opt;

	return *this;
}

Server::~Server(void)
{
	return ;
}

void Server::start(void)
{
	string s_server_port;
	std::ostringstream temp; 
	fd_set	readfds;
	if (bind(_master_socket, (struct  sockaddr *)& _address, sizeof(_address)) < 0)
	{
		std::cout << "Can't bind address" << std::endl;
		return ;
	}
	_addrlen = sizeof(_address);
	temp << _server_port;
	s_server_port = temp.str();
	log(std::string("Listening on port ") + s_server_port);
	if (listen(_master_socket, 5) < 0)
	{
		std::cout << "Listen error";
		return ;
	}
	log("Waiting connections");
	_run(readfds);
	return;
}

void Server::send_all()
{
	for (iterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->getBuffer().size())
			write((*it)->getFd(), (*it)->getBuffer().c_str(), (*it)->getBuffer().length());
		(*it)->getBuffer().clear();
	}
}

const std::string & Server::getPass() const
{ return (_server_password); }

const std::vector<User*> & Server::getUsers() const
{ return (_users); }

User & Server::getUser(std::string const & name)
{
	iterator it = _users.begin();

	while (it != _users.end())
	{
		if ((*it)->getName() == name)
			return (**it);
		it++;
	}
	throw UserNotFoundException();
}

bool	Server::isUser(std::string const & name)
{
	try {
		getUser(name);
	}
	catch(std::exception & e) {
		return false;
	}
	return true;
}

bool	Server::isUser(ITarget const & target)
{
	return (target.getName()[0] != '#');
}

bool Server::isChannel(std::string const & name)
{
	channel_iterator it;

	it = _channels.find(name);
	return (it != _channels.end());
}

bool Server::isFull(void)
{
	return (_users.size() > _slots);
}

void	Server::kickAll()
{
    for (iterator it = _users.begin(); it != _users.end(); it++)
		(*it)->kick();
}

Channel & Server::createChannel(std::string const & name, User & owner)
{
	std::pair<channel_iterator, bool> ret;

	ret = _channels.insert(std::make_pair(name, new Channel(name, owner)));
	if (!ret.second)
		throw std::exception();
	return (*(*ret.first).second);
}

Channel & Server::getChannel(std::string const & name)
{
	channel_iterator it;

	it = _channels.find(name);
	if (it == _channels.end())
		throw ChannelNotFoundException();
	return (*it->second);
}

ITarget & Server::getTarget(std::string const & name)
{
	if ((const char)name[0] == '#')
		return (getChannel(name));
	return (getUser(name));
}

const std::string Server::getMotd(User const & user) const
{
	std::string	buffer;

	buffer.append("372 " + user.getName() + ":              ______                                   \n");
	buffer.append("372 " + user.getName() + ":             /\\  _  \\                                  \n");
	buffer.append("372 " + user.getName() + ":             \\ \\ \\L\\ \\  _ __    __       __     ___    \n");
	buffer.append("372 " + user.getName() + ":              \\ \\  __ \\/\\`'__\\/'__`\\   /'_ `\\  / __`\\  \n");
	buffer.append("372 " + user.getName() + ":               \\ \\ \\/\\ \\ \\ \\//\\ \\L\\.\\_/\\ \\L\\ \\/\\ \\L\\ \\ \n");
	buffer.append("372 " + user.getName() + ":                \\ \\_\\ \\_\\ \\_\\\\ \\__/.\\_\\ \\____ \\ \\____/ \n");
	buffer.append("372 " + user.getName() + ":                 \\/_/\\/_/\\/_/ \\/__/\\/_/\\/___L\\ \\/___/  \n");
	buffer.append("372 " + user.getName() + ":                                         /\\____/       \n");
	buffer.append("372 " + user.getName() + ":                                         \\_/__/        \n");
	buffer.append("372 " + user.getName() + ":                                                        \n");			
	buffer.append("372 " + user.getName() + ":                      ______   ____    ____       \n");
	buffer.append("372 " + user.getName() + ":                     /\\__  _\\ /\\  _`\\ /\\  _`\\     \n");
	buffer.append("372 " + user.getName() + ":                     \\/_/\\ \\/ \\ \\ \\L\\ \\ \\ \\/\\_\\   \n");
	buffer.append("372 " + user.getName() + ":                        \\ \\ \\  \\ \\ ,  /\\ \\ \\/_/_  \n");
	buffer.append("372 " + user.getName() + ":                         \\_\\ \\__\\ \\ \\\\ \\\\ \\ \\L\\ \\ \n");
	buffer.append("372 " + user.getName() + ":                         /\\_____\\\\ \\_\\ \\_\\ \\____/ \n");
	buffer.append("372 " + user.getName() + ":                         \\/_____/ \\/_/\\/ /\\/___/  \n");
	return (buffer);
}

const std::map<std::string, Channel*> & Server::getChannelMap(void) const
{ return _channels; }

void	Server::shutdown(void) 
{
	std::cout << "\r\n||| Shutdown IRC serv by SIGINT |||" << std::endl;
	kickAll();
	send_all();
	_remove_disconnect();
	close(_master_socket);
	_master_socket = -1;
	_users.clear();
	for (std::pair<std::string, Channel *> channel : getChannelMap())
		delete (channel.second);
	_channels.clear();
	log("Bye");
	_status = 0;
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
		return ;
	}
	std::cout << timer << "[Server][Info] " << message << std::endl;
}

const char * Server::UserNotFoundException::what() const throw()
{ return ("User not found"); }

const char * Server::ChannelNotFoundException::what() const throw()
{ return ("Channel not found"); }
