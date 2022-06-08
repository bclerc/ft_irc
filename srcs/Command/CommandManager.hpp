#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP
 
# include <iostream>
# include <cstring>
# include <map>
# include "../../includes/Server.hpp"
# include "../User/User.hpp"

class User;

class CommandManager {

    public:
		typedef void (*CommandFunc)(CommandManager & , std::vector<std::string> & );
		typedef std::map<std::string, CommandFunc>::iterator iterator;
		typedef	std::pair<std::string, CommandFunc>	pair;

		User &	getSender();
        CommandManager(User * sender, char *request);
        CommandManager(CommandManager & cpy);
        ~CommandManager (void);


    private:
        User * 	 sender;

		std::map<std::string, CommandFunc>	_cmd_registre;

        CommandManager (void);


};

void	nickCommand(CommandManager & command, std::vector<std::string> & args);

#endif