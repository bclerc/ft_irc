
#include "User.hpp"

User::User(int & fd)
: _fd(fd), _nick("*"),  _status(UNREGISTER), _mode(0)
{
	return ;
}

User::User(void)
: _fd(-1), _nick("*"), _status(UNREGISTER), _mode(0)
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
    _fd                 = rhs._fd;
    _nick               = rhs._nick;
    _mode               = rhs._mode;
    _buffer             = rhs._buffer;
    _status             = rhs._status;
    _username           = rhs._username;
    _hostname           = rhs._hostname;
    _realname           = rhs._realname;
    _operator           = rhs._operator;
    _servername         = rhs._servername;
    _current_channel    = rhs._current_channel;
    
	return *this;
}

void    User::send(std::string const & request)
{
    _buffer += (request + "\r\n");
    log("> " + request );
    return ;
}

void    User::sendToChannels(std::string const & request)
{
    std::vector<Channel *>::iterator it;
    for (it = _current_channel.begin(); it != _current_channel.end(); it++)
        (*it)->sendWithOut(request, *this);
}

void   User::sendWithOut(std::string const & request, ITarget & out)
{
	(void)out;
	send(request);
	return ;
}

void User::kick(std::string const & reason)
{
    _buffer.clear();
    if (isOnChannel())
    {
        for (std::vector<Channel *>::iterator it = _current_channel.begin(); it != _current_channel.end(); it++)
        {
            (*it)->sendWithOut(":" + getPrefix() + " QUIT :" + reason, *this);
            (*it)->removeUser(*this);
        }
    }
    this->send(":" + getPrefix() + " QUIT :" + reason);
    setStatus(User::DISCONNECT);
}

void User::kill(std::string const & reason)
{
    _buffer.clear();
    if (isOnChannel())
    {
        for (std::vector<Channel *>::iterator it = _current_channel.begin(); it != _current_channel.end(); it++)
        {
            (*it)->sendWithOut(":" + getPrefix() + " kill :" + reason, *this);
            (*it)->removeUser(*this);
        }
    }
    this->send(":" + getPrefix() + " kill :" + reason);
    setStatus(User::DISCONNECT);
}

void User::setNick(std::string const nick)
{
	if (isOnChannel())
        sendToChannels(":" + getName() + " NICK " + nick);
	this->send(":" + getName() + " NICK " + nick);
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
{ _current_channel.push_back(&channel); }

void User::setChannel(Channel * channel)
{ _current_channel.push_back(channel); }

void User::removeChannel(Channel * channel)
{
    std::vector<Channel *>::iterator it;

    for (it = _current_channel.begin(); it != _current_channel.end(); it++)
    {
        if (*it == channel)
        {
            _current_channel.erase(it);
            break ;
        }
    }
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

const std::string User::getPrefix() const
{ return (isRegister() ? getName() + "!" + getUserName()+ "@"  + getServerName() : "*"); }

const  std::string & User::getName() const
{ return _nick; }

bool	User::isRegister(void) const 
{ return (_status > UNREGISTER_PASS); }

bool User::isConnected(void) const
{ return (_status != DISCONNECT); }

bool User::isOperator(void) const
{ return (_operator); }

bool User::isOnChannel(void) const
{
	if (!_current_channel.size())
		return false;
	return true;
}

bool User::isOnChannel(std::string const & channel) const
{
    std::vector<Channel *>::const_iterator it;

    for (it = _current_channel.begin(); it != _current_channel.end(); it++)
    {
        if ((*it)->getName() == channel)
            return true;
    }
    return false;
}

void	User::log(std::string const message) const
{
	server.log("(" + std::to_string(_fd)+ ") " + _nick + ": "  + message);
}

User::~User(void)
{
    _buffer.clear();
    delete this;
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