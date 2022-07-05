# include "../CommandManager.hpp"

void quitCommand(CommandManager::Command & command)
{
    command.sender->kick();
	return ;
}