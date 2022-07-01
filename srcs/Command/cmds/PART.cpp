# include "../CommandManager.hpp"

void partCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	try
	{
		Channel & channel = server.getChannel(command.args[0]);

		if (channel.isOnChannel(sender))
		{
			channel.send(":" + sender.getPrefix() + " PART " + channel.getName() + " :"  + command.trailer);
			channel.removeUser(sender);
			sender.setChannel(NULL);
		} else
			channel.send(RPL_NOTONCHANNEL(sender.getName(), channel.getName()));
	}
	catch (Server::ChannelNotFoundException & e)
	{
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
	}
}