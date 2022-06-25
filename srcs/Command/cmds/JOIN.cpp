# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
  User & sender = *command.sender;

  if (server.isChannel(command.args[0]) == true)
  {
    Channel & new_channel = server.getChannel(command.args[0]);
    sender.send(":" + sender.getNick() + " JOIN " + command.args[0]);
    new_channel.addUser(*command.sender);
  }
  if (server.isChannel(command.args[0]) == false)
  {
    Channel & new_channel = server.createChannel(command.args[0], *command.sender);
    sender.send(":" + sender.getNick() + " JOIN " + command.args[0]);
    new_channel.addUser(*command.sender);
  } 
}