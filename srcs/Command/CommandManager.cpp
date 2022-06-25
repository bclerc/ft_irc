#include "CommandManager.hpp"

void CommandManager::_register_cmds()
{
	_cmd_registre["PASS"] = passCommand;
	_cmd_registre["NICK"] = nickCommand;
    _cmd_registre["USER"] = userCommand;
	_cmd_registre["PING"] = pingCommand;
    _cmd_registre["MODE"] = modeCommand;
    _cmd_registre["QUIT"] = quitCommand;
    _cmd_registre["JOIN"] = quitCommand;
}

void CommandManager::_execute(Command & command)
{
    iterator cmd_it = _cmd_registre.find(command.command);

    if (cmd_it != _cmd_registre.end())
    {
        if (command.command != "PASS"
            && command.sender->getStatus() == User::UNREGISTER)
        {
            command.sender->kick(ERR_CLOSINGLINK(command.sender->getNick(), "", "", "No register"));
            return ;
        }
        if (command.sender->getStatus() != User::DISCONNECT)
            (*cmd_it->second)(command);
    }
    else
        command.sender->send("Command not found");
    command.args.clear();
}

/**
* @todo _build_args
* Un meilleur parsing, plus "efficace" car la je pense que je peux faire mieux quand meme
* 
*/
void CommandManager::_build_args(Command & command, std::string & request)
{
    size_t pos;
    bool   trailer;
    int    size = 0;
    
    std::string tmp;

    // I think this function is vraiment degueulasse.
    while ((pos = request.find(" ")) != std::string::npos) 
    {
        tmp = request.substr(0, pos);
        if (tmp[0] == ':')
            trailer = true;
        if (!size)
            command.command = tmp;
        else if (trailer)
            command.trailer += tmp + " ";
        else
            command.args.push_back(tmp);
        request.erase(0, pos + 1);
        size++;
    }
    if (trailer)
        command.trailer += request.substr(0, pos);
    else
        command.args.push_back(request.substr(0, pos));
    command.size = size + 1;
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

bool CommandManager::_ignore(std::string & request, const size_t & pos)
{
    std::vector<string>::iterator it;
    std::vector<string> cmd({"CAP", "WHOIS"}); // MODE a faire

    for (it = cmd.begin(); it != cmd.end(); it++)
    {
        if ((*it) == request.substr(0, (*it).size()))
        {
            request.erase(0, pos + 1);
            server.log("Ignoring command: " + *it);
            return true;
        }
    }
    return false;
}

/**
* @todo execCommand
* Reverifier pour le \r\n psk c'est louche la
*/
void CommandManager::execCommand(User * sender, char *request)
{
    Command command;
    std::string req(request);
    std::string line;
    size_t pos;

    command.sender = sender;
    while ((pos = req.find("\n")) != std::string::npos) 
    {
        if (_ignore(req, pos))
            continue;
        line = req.substr(0, pos - 1);
        sender->log(line);
        _build_args(command, line);
        _execute(command);
        req.erase(0, pos + 1);
    }
}

CommandManager::~CommandManager(void)
{
    return ;
}
