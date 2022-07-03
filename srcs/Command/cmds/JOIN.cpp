# include "../CommandManager.hpp"


void execute_join(CommandManager::Command & command, std::string channel_name,  std::string & cmd, size_t & pos)
{
	User & sender = *command.sender;

	Channel & channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
	channel.addUser(*command.sender);
	sender.setChannel(channel);
	 std::string name_User;
	const_iterator it_user = channel.getUsers().begin();
	name_User += "";
	while (it_user != channel.getUsers().end())
	{
		if (channel.isOperator(*it_user))
			name_User += "@" + (*it_user)->getName();
		else
			name_User +="+" + (*it_user)->getName();
		if (it_user + 1 != channel.getUsers().end())
			name_User += " ";
		++it_user;
	}
	sender.send(RPL_NAMREPLY(sender.getPrefix(), sender.getName(), channel.getName(), name_User));
	sender.send(RPL_ENDOFNAMES(sender.getPrefix(), sender.getName(), channel.getName()));
	channel.send(":" + sender.getPrefix() + " JOIN :" + channel.getName());
}

void	join_channel(CommandManager::Command & command, User & sender)
{	
	size_t pos;
	std::string cmd(command.args[0]);
	std::string	channel_name;	

	while (cmd.size() > 0)
	{
		try {
			pos = cmd.find(",");
			channel_name = cmd.substr(0, pos == std::string::npos ? cmd.size() : pos);
			execute_join(command, channel_name, cmd, pos);
		} catch (Server::ChannelNotFoundException & e) {
			sender.send(ERR_NOSUCHCHANNEL(sender.getName(), channel_name));
		}
		cmd.erase(0, pos == std::string::npos ? cmd.size() : pos + 1);
	}
}

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	
	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
        return ;
	}
	join_channel(command, sender);
	return ;
}