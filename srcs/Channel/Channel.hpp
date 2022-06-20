#ifndef CHANNEL_HPP
# define CHANNEL_HPP
 
# include <iostream>
# include "../User/User.hpp"

class User;

class Channel {

    public:

        Channel (void);
        Channel (std::string const & name, User & owner);
        Channel(Channel const & cpy);
        ~Channel (void);


    private:
        User         *          _owner;
        std::string             _name;
        std::vector<User>       _users;

};

#endif