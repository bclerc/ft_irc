
#include "User.hpp"

User::User(int & fd) : _fd(fd), _status(UNREGISTER)
{

	return ;
}

User::User(void) : _fd(-1), _status(UNREGISTER)
{
	return ;
}

User::User(User const & cpy)
{
	*this = cpy;
	return ;
}

User & User::operator=(User const & rhs)
{
	(void)rhs;
    _fd = rhs._fd;
    _nick = rhs._nick;
    _status = rhs._status;
    _username = rhs._username;
    _hostname = rhs._hostname;
    _servername = rhs._servername;
    _realname = rhs._realname;
    _buffer = rhs._buffer;
	return *this;
}

std::string & User::getBuffer()
{
    return _buffer;
}

void    User::send(std::string const & request)
{
    _buffer += (request + "\n");
    log(("From server: " + request));
    return ;
}

void    User::setNick(std::string const nick)
{
    _nick = nick;
    return ;
}

void User::setStatus(Status status)
{
	_status = status;
}

void User::setUserName(std::string const username)
{
    _username = username;
}

void User::setHostName(std::string const hostname)
{
    _hostname = hostname;
}

void User::setServerName(std::string const servername)
{
    _servername = servername;
}

void User::setRealName(std::string const realname)
{
    _realname = realname;
}

const std::string & User::getUserName() const { return _username; }
const std::string & User::getHostName() const { return _hostname; }
const std::string & User::getServerName() const { return _servername; }
const std::string & User::getRealname() const { return _realname; };


const   int User::getFd() const
{
    return _fd;
}

const   User::Status & User::getStatus() const {
    return _status;
}


const  std::string & User::getNick() const
{
    return _nick;
}

void	User::log(std::string const message) const
{
	std::cout << "[";
	if (!_nick.empty())
		std::cout << _nick << " ";
	std::cout << "(" << _fd << ")] " << message << std::endl;
}	
void User::kick(std::string const & reason)
{
    _buffer.clear();
    send(reason);
    setStatus(DISCONNECT);
}
User::~User(void)
{
    return ;
}
