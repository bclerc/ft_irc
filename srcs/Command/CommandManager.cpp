#include "CommandManager.hpp"

void CommandManager::_register_cmds()
{
	_cmd_registre["NICK"] = nickCommand;
}

void CommandManager::_execute(std::vector<std::string> & args)
{
    iterator cmd_it = _cmd_registre.find(args[0]);

    if (cmd_it != _cmd_registre.end())
        (*cmd_it->second)(*this, args);
    else
        sender->send("Command not found");
}


void CommandManager::_build_args(std::vector<std::string> & args, char *request)
{
    char *line;

    line = strtok(request, " ");
    while (line != NULL)
    {
        args.push_back(line);
        line = strtok (NULL, " ");
    }
    return ;
}

CommandManager::CommandManager(User * sender, char *request) : sender(sender)
{
    char * pch;
    std::vector<std::string> args;

    _register_cmds();
    pch = strtok(request, "\n\r");
    while (pch != NULL)
    {
        sender->log(pch);
        _build_args(args, request);
        _execute(args);
        pch = strtok (NULL, "\n\r");
        args.clear();
    }
    return ;
}

CommandManager::CommandManager(void)
{
    return ;
}

CommandManager::CommandManager(CommandManager & cpy)
{
    *this = cpy;
    return ;
}

User & CommandManager::getSender()
{
	return *sender;
}

CommandManager::~CommandManager(void)
{
    return ;
}
