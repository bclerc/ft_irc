#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP
 
# include <iostream>
# include <cstring>
# include "../../includes/Server.hpp"
# include "../User/User.hpp"

class User;

class CommandManager {

    public:
        CommandManager(User * sender, char *request);
        CommandManager(CommandManager & cpy);
        ~CommandManager (void);


    private:
        User * sender;
        CommandManager (void);

};

#endif