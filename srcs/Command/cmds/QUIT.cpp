# include "../CommandManager.hpp"

void quitCommand(CommandManager::Command & command)
{
    command.sender->setStatus(User::DISCONNECT);
    command.sender->kick(command.trailer);
	return ;
}