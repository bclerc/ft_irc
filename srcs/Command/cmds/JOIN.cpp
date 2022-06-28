# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
  std::string RPL_NAMERPL = ":";
	Channel & new_channel = server.isChannel(command.args[0]) ?  server.getChannel(command.args[0]) : server.createChannel(command.args[0], *command.sender);	
	
	new_channel.addUser(*command.sender);
	sender.send(":" + sender.getNick() + " JOIN " + new_channel.getName());

  const_iterator it = new_channel.getUsers().begin();

    RPL_NAMERPL +=" 353 " + sender.getNick();
    RPL_NAMERPL += " " + new_channel.getName() + " :";
    while (it != new_channel.getUsers().end())
    {
	    RPL_NAMERPL += " ";
	    if (new_channel.isOperator(*it))
	      RPL_NAMERPL += "@";
    	RPL_NAMERPL += it->getNick();
    	++it;
    }
   
   sender.send(RPL_NAMERPL);
   
}