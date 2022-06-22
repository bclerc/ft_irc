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

void Channel::setOperator(User & user)
{
	_operator.push_back(user);
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

Channel::~Channel(void)
{
    return ;
}
