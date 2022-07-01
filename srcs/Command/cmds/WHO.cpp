# include "../CommandManager.hpp"

void	whoCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	sender.send(":" + sender.getPrefix() + " 315 " + sender.getName() + " " +  sender.getName() + " :End of /WHO list.");
	
}