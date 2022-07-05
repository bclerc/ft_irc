# include "../CommandManager.hpp"

void execute_names(CommandManager::Command & command, std::string channel_name)
{
	User & sender = *command.sender;

	if(!server.isChannel(channel_name))
	{
		sender.send(RPL_ENDOFNAMES(sender.getPrefix(), sender.getName(), channel_name));
		return ;	
	}
	Channel & channel =  server.getChannel(channel_name);
	std::string name_User;
	const_iterator it_user = channel.getUsers().begin();
	while (it_user != channel.getUsers().end())
	{
		name_User += (*it_user)->getName();
		++it_user;
	}
	sender.send(RPL_NAMREPLY(sender.getPrefix(), sender.getName(), channel.getName(), name_User));
	sender.send(RPL_ENDOFNAMES(sender.getPrefix(), sender.getName(), channel.getName()));
}

void	names_parse(CommandManager::Command & command)
{	
	size_t pos;
	std::string cmd(command.args[0]);
	std::string	channel_name;	

	while (cmd.size() > 0)
	{
		pos = cmd.find(",");
		channel_name = cmd.substr(0, pos == std::string::npos ? cmd.size() : pos);
		execute_names(command, channel_name);
		cmd.erase(0, pos == std::string::npos ? cmd.size() : pos + 1);
	}
}

void namesCommand(CommandManager::Command & command)
{
  	User & sender = *command.sender;
	
	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
        return ;
	}
	names_parse(command);
	return ;
}
