#include "CommandManager.hpp"

void CommandManager::_register_cmds()
{
	_cmd_registre["PASS"] = passCommand;
	_cmd_registre["NICK"] = nickCommand;
	_cmd_registre["PING"] = pingCommand;

}

void CommandManager::_execute(Command & command)
{
    iterator cmd_it = _cmd_registre.find(command.args[0]);

    if (cmd_it != _cmd_registre.end())
    {
        if (command.args[0] != "PASS"
            && command.sender->getStatus() == User::UNREGISTER)
        {
            command.sender->kick(ERR_CLOSINGLINK("", "", "No register"));
            return ;
        }
        if (command.sender->getStatus() != User::DISCONNECT)
            (*cmd_it->second)(command);
    }
    else
        command.sender->send("Command not found");
    command.args.clear();
}


void CommandManager::_build_args(std::vector<std::string> & args, std::string & request)
{
    size_t pos;
    std::string tmp;

    while ((pos = request.find(" ")) != std::string::npos) 
    {
        tmp = request.substr(0, pos);
        args.push_back(tmp);
        request.erase(0, pos + 1);
    }
    args.push_back(request.substr(0, pos));
    request.clear();
    return ;
}

CommandManager::CommandManager()
{
    _register_cmds();
    return ;
}


CommandManager::CommandManager(CommandManager & cpy)
{
    *this = cpy;
    return ;
}

void CommandManager::execCommand(User * sender, char *request)
{
    Command command;
    std::string req(request);
    std::string line;
    size_t pos;

    command.sender = sender;
    while ((pos = req.find("\n")) != std::string::npos) 
    {
        if (req.substr(0, 3) == "CAP")
        {
            req.erase(0, pos + 1);
            continue;
        }
        line = req.substr(0, pos - 1);
        sender->log(line);
        _build_args(command.args, line);
        _execute(command);
        req.erase(0, pos + 1);
    }
}

CommandManager::~CommandManager(void)
{
    return ;
}
