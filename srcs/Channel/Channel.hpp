#ifndef CHANNEL_HPP
# define CHANNEL_HPP
 
# include <iostream>
# include "../User/User.hpp"

class User;

class Channel : virtual public ITarget {

    public:

        Channel (void);
        Channel (std::string const & name);
        Channel (std::string const & name, User & owner);
        Channel(Channel const & cpy);
        Channel & operator=(Channel const & rhs);
        ~Channel (void);

        void addUser(User & user);
        void removeUser(User & User);
        void setOperator(User & user, bool mode);
		void send(std::string const & message);

        bool isOnChannel(User const & user) const;
        bool isOperator(User const & user)  const;

        const std::vector<User> & getUsers() const;
        const std::string & getName(void) const;
    private:
        User         *          _owner;
        std::string             _name;
        std::vector<User>       _users;
        std::vector<User>       _operator;

};

#endif 