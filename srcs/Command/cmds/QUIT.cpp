# include "../CommandManager.hpp"

void quitCommand(CommandManager::Command & command)
{
    command.sender->setStatus(User::DISCONNECT);
    command.sender->send("bclerc!bclerc@localhost QUIT: " + command.trailer);
	return ;
}