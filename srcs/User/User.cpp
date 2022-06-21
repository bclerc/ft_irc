
#include "User.hpp"

User::User(int & fd)
: _fd(fd), _nick("*"),  _status(UNREGISTER), _mode(0)
{
    _current_channel = NULL;
	return ;
}

User::User(void)
: _fd(-1), _nick("*"), _status(UNREGISTER), _mode(0)
{
    _current_channel = NULL;
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
    _mode = rhs._mode;
    _buffer = rhs._buffer;
    _status = rhs._status;
    _username = rhs._username;
    _hostname = rhs._hostname;
    _realname = rhs._realname;
    _operator = rhs._operator;
    _servername = rhs._servername;
    _current_channel = rhs._current_channel;
	return *this;
}


void    User::send(std::string const & request)
{
    _buffer += (request + "\r\n");
    log("> " + request );
    return ;
}

void User::kick(std::string const & reason)
{
    _buffer.clear();
    send(getPrefix() + " QUIT: " + reason);
    setStatus(DISCONNECT);
}


void User::setNick(std::string const nick)
{
    send(":" + (isRegister() ? _nick : "*") + " NICK " + nick);
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

void User::setOperator(bool value)
{
    _operator = value;
}

void User::setChannel(Channel & channel)
{ _current_channel = &channel; }

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

const std::string User::getPrefix() const
{
    if (_nick.size())
        return (getNick() + "!" + getUserName()+ "@"  + getServerName());
     return ("*");
}

const  std::string & User::getNick() const
{ return _nick; }

Channel & User::getChannel(void)
{
    if (!_current_channel) 
        throw std::exception();         //Pareil, creer une exception
    return (*_current_channel);
}

bool	User::isRegister(void) const 
{ return (_status == REGISTER); }

bool User::isConnected(void) const
{ return (_status != DISCONNECT); }

bool User::isOperator(void) const
{ return (_operator); }

void	User::log(std::string const message) const
{
	server.log("(" + std::to_string(_fd)+ ") " + _nick + ": "  + message);
}

User::~User(void)
{
    _buffer.clear();
    return ;
}

bool User::operator==(const User & rhs)
{
    return (getFd() == rhs.getFd());
}

bool User::operator!=(const User & rhs)
{
    return (!(*this == rhs));
}