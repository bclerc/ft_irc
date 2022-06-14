# include "../CommandManager.hpp"

void passCommand(CommandManager::Command & command)
{
    std::cout << "Size: " << command.size << std::endl;
    if (command.size < 2)
    {
        command.sender->send(ERR_NEEDMOREPARAMS("PASS"));
        return ;
    }
    if (command.sender->getStatus() >= User::REGISTER)
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