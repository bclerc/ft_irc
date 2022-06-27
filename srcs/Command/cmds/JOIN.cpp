# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	Channel & new_channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
	
	new_channel.addUser(*command.sender);
	new_channel.sendAll("JOIN :" + command.args[0]);
}