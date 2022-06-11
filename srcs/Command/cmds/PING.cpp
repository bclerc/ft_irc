# include "../CommandManager.hpp"

void pingCommand(CommandManager::Command & command)
{
    command.sender->log("PONG");
	command.sender->send(("PONG " + command.args[1] + " :" + command.args[1]));
	return ;
}