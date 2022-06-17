# include "../CommandManager.hpp"

/**
* @todo nickCommand
*  Il faut check d'autres erreurs ici (ERR_ERRONEUSNICKNAME, ERR_NICKCOLLISION)
*  Et par la meme occasion defininr une limite de taille pour le pseudo
*/
void nickCommand(CommandManager::Command & command)
{
	if (command.size < 2)
	{
		command.sender->send(ERR_NONICKNAMEGIVEN());
		return ;
	}
	if (server.isUser(command.args[0]))
	{
		command.sender->send(ERR_NICKNAMEINUSE(command.args[0]));
		return;
	}
	command.sender->send(":* NICK " + command.args[0]);
	command.sender->setNick(command.args[0]);
	return ;
}