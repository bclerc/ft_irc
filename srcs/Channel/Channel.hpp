#ifndef CHANNEL_HPP
# define CHANNEL_HPP
 
# include <iostream>
# include "../User/User.hpp"

class User;

class Channel {

    public:
        Channel (void);
        Channel (std::string const & name);
        Channel(Channel & cpy);
        ~Channel (void);


    private:
        std::string             _name;
        std::vector<User>       _users;

};

#endif