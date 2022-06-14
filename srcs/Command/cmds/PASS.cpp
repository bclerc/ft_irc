# include "../CommandManager.hpp"

void passCommand(CommandManager::Command & command)
{
    if (command.args.size() < 2)
    {
        command.sender->send(ERR_NEEDMOREPARAMS("PASS"));
        return ;
    }
    if (command.sender->getStatus() >= User::Status::REGISTER)
    {
        command.sender->send(ERR_ALREADYREGISTRED());
        return ;
    }
    if (server.getPass() == command.args[1])
        command.sender->setStatus(User::Status::UNREGISTER_PASS);
    else 
        command.sender->kick(ERR_CLOSINGLINK("", "", "Bad password"));
    return ;
}