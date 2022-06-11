# include "../CommandManager.hpp"

void nickCommand(CommandManager::Command & command)
{

	command.sender->setNick(command.args[1]);
	command.sender->send("001 * bclerc :Nickname is already in use");
	return ;
}