# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
 	std::string name_User;
	
	if (command.size == 2)
	{	
		Channel & channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
		channel.addUser(*command.sender);
		sender.setChannel(channel);
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
	else
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
        return ;
    }
}