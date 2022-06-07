#include "User.hpp"


User::User(int & fd) : _fd(fd), _status(Status::UNREGISTER)
{

	return ;
}

User::User(void) : _fd(-1), _status(Status::UNREGISTER)
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
	return *this;
}

std::string & User::getBuffer()
{
    return _buffer;
}

void    User::send(std::string const & request)
{
    _buffer += (request + "\n\r");
    return ;
}

void    User::setNick(std::string const & nick)
{
    _nick = nick;
    return ;
}

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

User::~User(void)
{
    return ;
}
