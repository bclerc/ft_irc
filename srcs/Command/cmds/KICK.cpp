# include "../CommandManager.hpp"

void kickCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	Channel & channel = server.getChannel(command.args[0]);

	if (command.args.size() < 2)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return;
	}
	if(server.isChannel(command.args[0]) == false)
	{
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
		return;
	}
	if(sender.isOnChannel(command.args[0]) == false)
	{
		sender.send(ERR_NOTONCHANNEL(sender.getName(), command.args[0]));
		return;
	}
	if(!sender.isOperator())
	{
		sender.send(ERR_CHANOPRIVSNEEDED(sender.getName(), command.args[0]));
		return;
	}
	if (sender.isOnChannel(command.args[1]))
	{
		sender.send(ERR_USERNOTINCHANNEL(sender.getName(), command.args[0], command.args[1]));
		return;
	}
	channel.removeUser(command.args[1]);
	sender.removeChannel(&channel);
	channel.send(":" + sender.getPrefix() + " KICK " + command.args[0] + " " + command.args[1] +  " " + command.trailer);
//	sender.send(":" + sender.getPrefix() + " KICK " + command.args[0] + " " + command.args[1] +  " " + command.trailer);
}