#include "Channel.hpp"

Channel::Channel(std::string const & name, User & owner)
: _name(name), _owner(&owner), _max_size(20), _invite_only(false)
{
	setOperator(owner, true);
    return ;
}

Channel::Channel(void): _max_size(20), _invite_only(false)
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
	_users.push_back(&user);
}

void Channel::removeUser(User & User)
{
	for (iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (*it == &User)
		{
			_users.erase(it);
			return ;
		}
	}
}

void Channel::removeUser(std::string user)
{
	for (iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->getName() == user)
		{
			_users.erase(it);
			return ;
		}
	}
}

void Channel::removeInvited(User & user)
{
	for (iterator it = _invited.begin(); it != _invited.end(); ++it)
	{
		if ((*it)->getName() == user.getName())
		{
			_invited.erase(it);
			return ;
		}
	}
}

void Channel::setOperator(User & user, bool op)
{
	if (!op)
	{
		for (iterator it = _operator.begin(); it != _operator.end(); it++)
		{
			if (*it == &user)
			{
				_operator.erase(it);
				break ;
			}
		}
		return ; 
	} else
		_operator.push_back(&user);
}

Channel & Channel::operator=(Channel const & rhs)
{
    _owner = rhs._owner;
    _name = rhs._name;
    _users = rhs._users;
    _operator = rhs._operator;
	_max_size = rhs._max_size;
    return *this;
}

void Channel::send(std::string const & message)
{
	for (iterator it = _users.begin(); it != _users.end(); it++)
		(*it)->send(message);
}

void Channel::sendWithOut(std::string const & message, ITarget & out)
{
	for (iterator it = _users.begin(); it != _users.end(); it++)
		if (*it != &out)
			(*it)->send(message);
}

void Channel::setTopic(std::string const & topic)
{
	_topic = topic;
}

void Channel::invite(User & user)
{
	_invited.push_back(&user);
}

void Channel::setInviteOnly(bool mode) 
{
	_invite_only = mode;
}

bool Channel::isOperator(User const & user) const
{
	return isOperator(&user);
}

bool Channel::isOperator(User const * user) const
{
	std::vector<User*>::const_iterator it = _operator.begin();

	for (; it != _operator.end(); it++)
	{
		if (*it == user)
			return true;
	}
	return false;
}

bool Channel::isOnChannel(User const & user) const
{
	std::vector<User*>::const_iterator it = _users.begin();

	for (; it != _users.end(); it++)
	{
		if (*it == &user)
			return true;
	}
	return false;
}

bool Channel::isInvited(User const & user) const
{
	std::vector<User*>::const_iterator it = _invited.begin();

	for (; it != _invited.end(); it++)
	{
		if (*it == &user)
			return true;
	}
	return false;
}

bool Channel::isFull(void) const
{
	return (_users.size() >= _max_size);
}

bool Channel::isInviteOnly(void) const 
{
	return (_invite_only);
}

const std::string & Channel::getName(void) const
{
	return _name;
}

const std::string & Channel::getTopic(void) const
{
	return _topic;
}

const std::vector<User*> & Channel::getUsers() const
{ return _users; }

Channel::~Channel(void)
{
    return ;
}
