# include "../CommandManager.hpp"

void pingCommand(CommandManager::Command & command)
{
	std::string ret = command.size > 1 ? (command.args[0] + " :" + command.args[0]) : "";
	command.sender->send("PONG " + ret);
	return ;
}