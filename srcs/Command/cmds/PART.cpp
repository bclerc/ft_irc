# include "../CommandManager.hpp"

void execute_part(CommandManager::Command & command, std::string channel_name,  std::string & cmd, size_t & pos)
{
	std::string	quitmsg = command.trailer.size() ? command.trailer : "Leaving";
	User & sender = *command.sender;

	Channel & channel = server.getChannel(channel_name);

	if (channel.isOnChannel(sender))
	{
		channel.send(":" + sender.getPrefix() + " PART " + channel.getName() + " :"  + quitmsg);
		channel.removeUser(sender);
		sender.removeChannel(&channel);
	} else
		sender.send(RPL_NOTONCHANNEL(sender.getName(), channel.getName()));
}

void quit_user(CommandManager::Command & command, User & sender)
{
	size_t pos;
	std::string cmd(command.args[0]);
	std::string	channel_name;

	while (cmd.size() > 0)
	{
		try {
			pos = cmd.find(",");
			channel_name = cmd.substr(0, pos == std::string::npos ? cmd.size() : pos);
			execute_part(command, channel_name, cmd, pos);
		} catch (Server::ChannelNotFoundException & e) {
			sender.send(ERR_NOSUCHCHANNEL(sender.getName(), channel_name));
		}
		cmd.erase(0, pos == std::string::npos ? cmd.size() : pos + 1);
	}
}

void partCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	quit_user(command, sender);
	return ;
}