# include "../CommandManager.hpp"

void passCommand(CommandManager::Command & command)
{
    if (command.size < 2)
    {
        command.sender->send(ERR_NEEDMOREPARAMS("PASS"));
        return ;
    }
    if (command.sender->isRegister())
    {
        command.sender->send(ERR_ALREADYREGISTRED());
        return ;
    }
    if (server.getPass() == command.args[0])
        command.sender->setStatus(User::UNREGISTER_PASS);
    else 
        command.sender->kick(ERR_CLOSINGLINK("", "", "Bad password"));
 
    return ;
}