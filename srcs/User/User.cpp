
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


void    User::send(std::string const & request)
{
    _buffer += (request + "\n");
    log(("From server: " + request));
    return ;
}

/**
* @todo kick
* Pas bonne utilisation, reverifier comment kick a un user
*/
void User::kick(std::string const & reason)
{
    _buffer.clear();
    send(reason);
    setStatus(DISCONNECT);
}

/**
* @todo setNick
* Confirmer le changement de nick au server directement dans le setNick ou pas. Tel est la question
* Je pense que oui. A reflechir.
*/
void User::setNick(std::string const nick)
{
    _nick = nick;
    return ;
}

void User::setStatus(Status status)
{
	_status = status;
	return ;
}

void User::setUserName(std::string const username)
{
    _username = username;
	return ;
}

void User::setHostName(std::string const hostname)
{
    _hostname = hostname;
	return ;
}

void User::setServerName(std::string const servername)
{
    _servername = servername;
	return ;
}

void User::setRealName(std::string const realname)
{ 
	_realname = realname; 
	return ;
}

const std::string & User::getUserName() const
{ return _username; }

const std::string & User::getHostName() const
{ return _hostname; }

const std::string & User::getServerName() const
{ return _servername; }

const std::string & User::getRealname() const
{ return _realname; };

const   User::Status & User::getStatus() const 
{ return _status; }

std::string & User::getBuffer()
{ return _buffer; }

const   int & User::getFd() const
 { return _fd; }

const  std::string & User::getNick() const
{ return _nick; }

bool	User::isRegister(void) const 
{ return (_status == REGISTER); }

void	User::log(std::string const message) const
{
	std::cout << "[";
	if (!_nick.empty())
		std::cout << _nick << " ";
	std::cout << "(" << _fd << ")] " << message << std::endl;
}

User::~User(void)
{
    _buffer.clear();
    close(_fd);
    return ;
}
