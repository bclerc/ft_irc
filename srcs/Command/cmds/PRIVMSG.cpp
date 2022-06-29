# include "../CommandManager.hpp"

void privmsgCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
//	if (command.args[0][0] == '#')
//	{
		sender.send(":" + sender.getPrefix() + " " + command.args[1]);
//	}
//	else
//	{
//		sender.send(":" + sender.getPrefix() + " " + command.args[1]);
//	}
}
