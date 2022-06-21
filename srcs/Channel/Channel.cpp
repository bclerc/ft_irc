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

Channel::~Channel(void)
{
    return ;
}
