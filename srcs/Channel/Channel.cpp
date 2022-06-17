#include "Channel.hpp"

Channel::Channel(std::string const & name) : _name(name)
{
    return ;
}

Channel::Channel(void)
{
    return ;
}

Channel::Channel(Channel & cpy)
{
    *this = cpy;
    return ;
}

Channel::~Channel(void)
{
    return ;
}
