# include "../CommandManager.hpp"

void killCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	if (command.size < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	if (!server.isUser(command.args[0]))
	{
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
		return ;
	}
	if(!sender.isOperator())
	{
		sender.send(ERR_NOPRIVILEGES(sender.getName()));
		return ;
	}
	User & target = server.getUser(command.args[0]);
    target.send(":" + sender.getPrefix() + " kill :" + command.trailer);
	target.kill();
}