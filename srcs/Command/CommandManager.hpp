#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP
 
# include <iostream>
# include <cstring>
# include <map>
# include <vector>

# include "rfc/replies.hpp"
# include "../User/User.hpp"
# include "../../includes/Server.hpp"

class User;
class Server;

class CommandManager {

    public:

        typedef struct Command {
            User *                      sender;
            int                         size;
            std::string                 command;
            std::string                 trailer;
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
        void    _build_args(Command & command, std::string & request);
        bool    _ignore(std::string & request, const size_t & pos);
        void    _execute(Command  & command);



};

void	nickCommand(CommandManager::Command & command);
void    pingCommand(CommandManager::Command & command);
void    passCommand(CommandManager::Command & command);
void    userCommand(CommandManager::Command & command);



#endif