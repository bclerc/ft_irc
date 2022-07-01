# include "../CommandManager.hpp"

/**
 * 
 * Voila ce que ca donne 
 * le target envoi le message a tous les users de la channel si channel (sans le sender (sendWithOut))
 * le target envoi le message a l'User si c'est un user. dans ce cas le sendWithOut fait juste un send normal
 * getTarget renvoi un exceptions si le target est un user/channel qui n'existe pas
 **/

void privmsgCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	try {
		ITarget & target = server.getTarget(command.args[0]); // Recupere un target (user/channel)
		target.sendWithOut(":" + sender.getName() + " PRIVMSG " + target.getName() + " :" + command.trailer, sender); 
	}
	catch (Server::ChannelNotFoundException & e) { // C'est un channel, mais il existe pas
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
	}
	catch (Server::UserNotFoundException & e) { // C'est un User, mais il existe pas
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
	}
}
