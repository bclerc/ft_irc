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
        void removeInvited(User & user);

        void setInviteOnly(bool mode);
        void setOperator(User & user, bool mode);
        void setTopic(std::string const & topic);

		void sendWithOut(std::string const & message, ITarget & out);
		void send(std::string const & message);
        void invite(User & user);

        bool isOnChannel(User const & user) const;
        bool isOperator(User const & user)  const;
        bool isOperator(User const * user)  const;
        bool isInvited(User const & user)   const;
        bool isFull(void)                   const;
        bool isInviteOnly(void)  const;


        const std::vector<User*> & getUsers() const;
        const std::string & getName(void) const;
        const std::string & getTopic(void) const;
    private:

		typedef std::vector<User*>::iterator iterator;

        bool                    _invite_only;
        size_t                  _max_size;
        User         *          _owner;
        std::string             _name;
        std::string             _topic;
        std::vector<User*>       _users;
        std::vector<User*>       _invited;
        std::vector<User*>       _operator;

};

#endif 