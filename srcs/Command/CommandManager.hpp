#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP
 
# include <iostream>
# include <cstring>
# include <map>
# include <vector>

# include "../../includes/Server.hpp"
# include "../User/User.hpp"

class User;

class CommandManager {

    public:
		typedef void (*CommandFunc)(CommandManager & , std::vector<std::string> & );
		typedef std::map<std::string, CommandFunc>::iterator iterator;

		User &	getSender();
        CommandManager(User * sender, char *request);
        CommandManager(CommandManager & cpy);
        ~CommandManager (void);


    private:
        User * 	 sender;

		std::map<std::string, CommandFunc>	_cmd_registre;
        
        void    _register_cmds();
        void    _build_args(std::vector<std::string> & args, char *request);
        void    _execute(std::vector<std::string> & args);
        CommandManager (void);


};

void	nickCommand(CommandManager & command, std::vector<std::string> & args);

#endif