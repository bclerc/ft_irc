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

        if (args[0] == "NICK")
        {
            sender->setNick(args[1]);
            sender->send(("Your Nick is now: ") + args[1]);
        }

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

CommandManager::~CommandManager(void)
{
    return ;
}
