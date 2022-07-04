# include "../CommandManager.hpp"

	/**
	 * Checker si le channel est full avec channel.isFull() 
	 * renvoyer la rpl ERR_CHANNELISFULL si c'est le cas
	 */

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
 	std::string name_user;
	

	if (command.size > 1)
	{	
		Channel & channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
		channel.addUser(*command.sender);
		sender.setChannel(channel);
		const_iterator it_user = channel.getUsers().begin();
		name_user += "";
		while (it_user != channel.getUsers().end())
		{
			if (channel.isOperator(*it_user))
				name_user += "@" + (*it_user)->getName();
			else
				name_user +="+" + (*it_user)->getName();
			if (it_user + 1 != channel.getUsers().end())
				name_user += " ";
			++it_user;
		}
		sender.send(RPL_NAMREPLY(sender.getPrefix(), sender.getName(), channel.getName(), name_user));
		sender.send(RPL_ENDOFNAMES(sender.getPrefix(), sender.getName(), channel.getName()));
		channel.send(":" + sender.getPrefix() + " JOIN :" + channel.getName());
	}
	else
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
        return ;
    }
}