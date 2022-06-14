# include "../CommandManager.hpp"

void nickCommand(CommandManager::Command & command)
{
	if (command.args.size() < 2)
	{
		command.sender->send(ERR_NONICKNAMEGIVEN());
		return ;
	}
	if (server.isUser(command.args[1]))
	{
		command.sender->send(ERR_NICKNAMEINUSE(command.args[1]));
		return;
	} 
	command.sender->setNick(command.args[1]);
	return ;
}