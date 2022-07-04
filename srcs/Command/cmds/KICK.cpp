# include "../CommandManager.hpp"

void execute_kick(CommandManager::Command & command)
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

	User & target = server.getUser(command.args[1]);

	channel.send(":" + sender.getPrefix() + " KICK " + command.args[0] + " " + command.args[1] +  " " + command.trailer);
	channel.removeUser(command.args[1]);
	target.removeChannel(&channel);
}

void kick_user(CommandManager::Command & command, User & sender)
{
	size_t pos;
	std::string cmd(command.args[0]);
	std::string	user_name;

	while (cmd.size() > 0)
	{
		try {
			pos = cmd.find(",");
			user_name = cmd.substr(0, pos == std::string::npos ? cmd.size() : pos);
			execute_kick(command);
		} 
		catch (Server::ChannelNotFoundException & e) {
			sender.send(ERR_USERNOTINCHANNEL(sender.getName(), command.args[0], command.args[1]));
		}
		cmd.erase(0, pos == std::string::npos ? cmd.size() : pos + 1);
	}
}

void kickCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	if (command.args.size() < 2)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return;
	}
	kick_user(command, sender);
}