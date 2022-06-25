#include "Channel.hpp"

Channel::Channel(std::string const & name, User & owner)
: _name(name), _owner(&owner)
{
    return ;
}

Channel::Channel(std::string const & name)
: _name(name)
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

Channel::~Channel(void)
{
    return ;
}
