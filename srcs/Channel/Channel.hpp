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
        void removeUser(std::string user);
        void setOperator(User & user, bool mode);
		void send(std::string const & message);
		void sendWithOut(std::string const & message, ITarget & out);

        bool isOnChannel(User const & user) const;
        bool isOperator(User const & user)  const;
        bool isOperator(User const * user)  const;
        bool isFull(void)                   const;


        const std::vector<User*> & getUsers() const;
        const std::string & getName(void) const;
    private:

		typedef typename std::vector<User*>::iterator iterator;

        size_t                  _max_size;
        User         *          _owner;
        std::string             _name;
        std::vector<User*>       _users;
        std::vector<User*>       _operator;

};

#endif 