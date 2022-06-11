# include "../CommandManager.hpp"

void nickCommand(CommandManager::Command & command)
{

	command.sender->setNick(command.args[1]);
	command.sender->log(("Change nickname to ") + command.args[1]);
	return ;
}