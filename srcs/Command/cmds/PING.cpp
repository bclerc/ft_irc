# include "../CommandManager.hpp"

void pingCommand(CommandManager::Command & command)
{
	command.sender->send(("PONG " + command.args[0] + " :" + command.args[0]));
	return ;
}