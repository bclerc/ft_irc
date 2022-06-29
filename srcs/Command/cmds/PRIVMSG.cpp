# include "../CommandManager.hpp"

/**
 * 
 * Voila ce que ca donne 
 * mais je crois que le message est pas dans le bon format
 **/

void privmsgCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	try {
		ITarget & target = server.getTarget(command.args[0]);
		target.send(":" + sender.getName() + " PRIVMSG " + target.getName() + " :" + command.trailer);
	}
	catch (Server::ChannelNotFoundException & e) {
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
	}
	catch (Server::UserNotFoundException & e) {
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
	}
}
