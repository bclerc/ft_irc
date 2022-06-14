# include "../CommandManager.hpp"

void nickCommand(CommandManager::Command & command)
{
	if (command.size < 2)
	{
		command.sender->send(ERR_NONICKNAMEGIVEN());
		return ;
	}
	if (server.isUser(command.args[0]))
	{
		command.sender->send(ERR_NICKNAMEINUSE(command.args[0]));
		return;
	} 
	command.sender->setNick(command.args[0]);
	return ;
}