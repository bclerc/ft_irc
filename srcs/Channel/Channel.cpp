#include "Channel.hpp"

Channel::Channel(std::string const & name, User & owner)
: _name(name), _owner(&owner)
{
    return ;
}

Channel::Channel(void)
{
    return ;
}

Channel::Channel(Channel const & cpy)
{
    *this = cpy;
    return ;
}

void Channel::addUser(User & user)
{
	_users.push_back(user);
}

void Channel::setOperator(User & user, bool op)
{
	if (!op)
	{
		for (iterator it = _operator.begin(); it != _operator.end(); it++)
		{
			if (*it == user)
			{
				_operator.erase(it);
				break ;
			}
		}
		return ; 
	} else {
		_operator.push_back(user);
	}
}

void Channel::sendAll(std::string const & message)
{
	for (iterator it = _users.begin(); it != _users.end(); it++)
		it->send(":" + it->getNick() + " ");
}

bool Channel::isOperator(User const & user) const
{
	std::vector<User>::const_iterator it = _operator.begin();

	for (; it != _operator.end(); it++)
	{
		if (it->getNick() == user.getNick())
			return true;
	}
	return false;
}

const std::string & Channel::getName(void) const
{
	return _name;
}

const std::vector<User> & Channel::getUsers() const
{ return _users; }

Channel::~Channel(void)
{
    return ;
}
