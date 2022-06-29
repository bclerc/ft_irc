# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
 	std::string name_User;
	std::vector<std::string> chan;
	
	Channel & new_channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
	chan.push_back(new_channel.getName());

	std::vector<std::string>::iterator it_chan = chan.begin();
	
	while (it_chan != chan.end())
	{
		new_channel.addUser(*command.sender);
		sender.send(":" + sender.getNick() + " JOIN :" + new_channel.getName());

	  	const_iterator it_user = new_channel.getUsers().begin();
	    while (it_user != new_channel.getUsers().end())
	    {
			name_User += " ";
		    if (new_channel.isOperator(*it_user))
		      name_User += "@" + it_user->getNick();
			else
	    		name_User +="+" + it_user->getNick();
	    	++it_user;
	    }
	   sender.send(RPL_NAMREPLY(sender.getPrefix(), sender.getNick(), new_channel.getName(), name_User));
	   sender.send(RPL_ENDOFNAMES(sender.getPrefix(), sender.getNick(), new_channel.getName()));
		++it_chan;
	}
}