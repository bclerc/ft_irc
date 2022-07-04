# include "../CommandManager.hpp"

void 	user_who(CommandManager::Command & command, User & sender)
{
	User & target = server.getUser(command.args[0]);

	sender.send("352 " + sender.getName() + " " + target.getName() + " " + target.getHostName() + " " + target.getServerName() + " H :0 " + target.getRealname());
	sender.send("315 " + sender.getName() + " " + target.getName() + " :End of /WHO list.");
}

void channel_who(CommandManager::Command & command, User & sender)
{
	std::string userlist;

	for (User * user : server.getChannel(command.args[0]).getUsers())
		userlist += user->getName() + " ";
	sender.send("315 " + sender.getName() + " " + userlist + " :End of /WHO list.");
}

void	whoCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	if (command.size < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	try
	{
		if (command.args[0][0] == '#')
			channel_who(command, sender);
		else
			user_who(command, sender);
	}
	catch(const Server::ChannelNotFoundException & e) {
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
	}
	catch(const Server::UserNotFoundException & e){
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
	}
}