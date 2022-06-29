# include "../CommandManager.hpp"

//channel msg

//user msg


void privmsgCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
//	User & target = server.getUser(command.args);
//	
//
//		server.getUser()
//	{
		sender.send(":" + sender.getPrefix() + " " + command.args[1]);
	//}
//	else
//	{
//		sender.send(":" + sender.getPrefix() + " " + command.args[1]);
//	}
}
