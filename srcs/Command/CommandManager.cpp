#include "CommandManager.hpp"

CommandManager::CommandManager(void)
{
    return ;
}

CommandManager::CommandManager(User * sender, char *request) : sender(sender)
{
    char * pch;
    char *test;
    std::vector<std::string> args;
	
	
	_cmd_registre["NICK"] = nickCommand;

    // Code de test, Absolument pas le code final, c'est degue, c'est normal
    pch = strtok(request, "\n\r");
    while (pch != NULL)
    {
        test = strtok(pch, " ");
        while (test != NULL)
        {
            args.push_back(test);
            test = strtok (NULL, " ");
        }

		iterator cmd_it = _cmd_registre.find(args[0]);
		if (cmd_it != _cmd_registre.end())
			(*cmd_it->second)(*this, args);

        sender->log(pch);
        pch = strtok (NULL, "\n\r");
        args.clear();
    }
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
