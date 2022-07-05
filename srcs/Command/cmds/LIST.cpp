# include "../CommandManager.hpp"

void execute_list(CommandManager::Command & command, std::string channel_name)
{
	User & sender = *command.sender;
	
	if(!server.isChannel(channel_name))
	{
		return ;
	}
	Channel & channel =  server.getChannel(channel_name);
	sender.send(RPL_LISTSTART(sender.getPrefix(), sender.getName()));
	sender.send(RPL_LIST(sender.getPrefix(), sender.getName(), channel.getName(), channel.getTopic()));
	sender.send(RPL_LISTEND(sender.getPrefix(), sender.getName()));

}

void	list_channel(CommandManager::Command & command)
{	
	size_t pos;
	std::string cmd(command.args[0]);
	std::string	channel_name;	

	while (cmd.size() > 0)
	{
		pos = cmd.find(",");
		channel_name = cmd.substr(0, pos == std::string::npos ? cmd.size() : pos);
		execute_list(command, channel_name);
		cmd.erase(0, pos == std::string::npos ? cmd.size() : pos + 1);
	}
}

void listCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	
	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
        return ;
	}
	list_channel(command);
	return ;
}