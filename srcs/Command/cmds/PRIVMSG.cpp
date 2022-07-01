# include "../CommandManager.hpp"

void privmsgCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	try {
		ITarget & target = server.getTarget(command.args[0]);
		if((server.isChannel(target.getName()) && sender.getChannel().getName() == target.getName()) || server.isUser(target.getName()))
			target.sendWithOut(":" + sender.getName() + " PRIVMSG " + target.getName() + " :" + command.trailer, sender); 
		else
			sender.send(ERR_CANNOTSENDTOCHAN(sender.getName(), command.args[0]));
	}
	catch (Server::ChannelNotFoundException & e) {
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
	}
	catch (Server::UserNotFoundException & e) {
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
	}
}
