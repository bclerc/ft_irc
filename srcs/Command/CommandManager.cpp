#include "CommandManager.hpp"

void CommandManager::_register_cmds()
{
    _cmd_registre["WHO"] = whoCommand;
	_cmd_registre["PASS"] = passCommand;
	_cmd_registre["NICK"] = nickCommand;
    _cmd_registre["USER"] = userCommand;
	_cmd_registre["PING"] = pingCommand;
    _cmd_registre["MODE"] = modeCommand;
    _cmd_registre["QUIT"] = quitCommand;
    _cmd_registre["JOIN"] = joinCommand;
    _cmd_registre["PART"] = partCommand;
	_cmd_registre["OPER"] = operCommand;
    _cmd_registre["TOPIC"] = topicCommand;
    _cmd_registre["PRIVMSG"] = privmsgCommand;
    _cmd_registre["NOTICE"] = privmsgCommand;
    _cmd_registre["KICK"] = kickCommand;
    _cmd_registre["INVITE"] = inviteCommand;
    _cmd_registre["kill"] = killCommand;

}

void CommandManager::_execute(Command & command)
{
    iterator cmd_it = _cmd_registre.find(command.command);

    if (cmd_it != _cmd_registre.end())
    {
        if (command.command != "PASS"
            && command.sender->getStatus() < User::UNREGISTER_PASS)
        {
            command.sender->kick("Not register");
            return ;
        }
        if (command.sender->getStatus() != User::DISCONNECT)
            (*cmd_it->second)(command);
    }
    else
        command.sender->send("Command not found");
    command.args.clear();
}

void CommandManager::_build_args(Command & command, std::string & request)
{
    size_t pos;
    bool   trailer = 0;
    int    size = 0;
    
    std::string tmp;
	command.trailer = "";
    while (request.size() > 0)
	{
		pos = request.find(" ");
		tmp = request.substr(0, pos == std::string::npos ? request.size() : pos);
		if (tmp[0] == ':')
		{
			trailer = 1;
			tmp.erase(0, 1);
		}
		if (!size)
			command.command = tmp;
		else if (trailer)
			command.trailer += tmp + (pos == std::string::npos ? "" : " ");
		else
			command.args.push_back(tmp);
		request.erase(0, pos == std::string::npos ? request.size() : pos + 1);
		size++;
	}
	command.size = size;
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
    std::vector<string> cmd({"CAP", "WHOIS"});

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

void CommandManager::execCommand(User * sender)
{
    Command command;
    std::string & req = sender->receive_buffer;
    std::string line;
    size_t pos;

    command.sender = sender;
    while ((pos = req.find("\n")) != std::string::npos) 
    {
        if (_ignore(req, pos))
            continue;
        line = req.substr(0, pos);
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
