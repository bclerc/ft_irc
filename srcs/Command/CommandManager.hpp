#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP
 
# include <iostream>
# include <cstring>
# include <map>
# include <vector>

# include "../User/User.hpp"

class User;

class CommandManager {

    public:

        typedef struct Command {
            User *                      sender;
            std::vector<std::string>    args;
        }              Command;

		typedef void (*CommandFunc)(Command &);
		typedef std::map<std::string, CommandFunc>::iterator iterator;

        
        CommandManager(void);
        CommandManager(CommandManager & cpy);
        ~CommandManager (void);

        void    execCommand(User * sender, char * request);

    private:
		std::map<std::string, CommandFunc>	_cmd_registre;

        void    _register_cmds();
        void    _build_args(std::vector<std::string> & args, std::string & request);
        void    _execute(Command  & command);



};

void	nickCommand(CommandManager::Command & comvvmand);

#endif