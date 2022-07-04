# include "../CommandManager.hpp"

void killCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	if (command.size < 2)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	if (!server.isUser(command.args[0]))
	{
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
		return ;
	}
	if (command.args[1].size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	if(!sender.isOperator())
	{
		sender.send(ERR_NOPRIVILEGES(sender.getName()));
		return ;
	}
	sender.send(":" + sender.getPrefix() + " KILL " + command.args[0] + " :" + command.trailer);
	server.getUser(command.args[1]).kill(command.trailer);
}