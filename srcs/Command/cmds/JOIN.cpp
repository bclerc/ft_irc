# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
 	std::string name_User;
	
	Channel & new_channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
	new_channel.addUser(*command.sender);
	sender.setChannel(&new_channel);

	std::vector<User*>::const_iterator it_user = new_channel.getUsers().begin();
	name_User += "";
	int counter = 0;
	

	while (it_user != new_channel.getUsers().end())
	{
		if (new_channel.isOperator(*it_user))
			name_User += "@" + (*it_user)->getName();
		else
			name_User +="+" + (*it_user)->getName();
		if (it_user + 1 != new_channel.getUsers().end())
			name_User += " ";
		++it_user;
	}
	sender.send(RPL_NAMREPLY(sender.getPrefix(), sender.getName(), new_channel.getName(), name_User));
	sender.send(RPL_ENDOFNAMES(sender.getPrefix(), sender.getName(), new_channel.getName()));
	new_channel.send(":" + sender.getPrefix() + " JOIN :" + new_channel.getName());
	
}