#include "../CommandManager.hpp"

void execute_topic(CommandManager::Command & command, User & sender)
{
    Channel & channel = server.getChannel(command.args[0]);
    
    std::cout << "Size: " << command.size << std::endl;
    if (command.size > 1)
    {
        if (channel.isOnChannel(sender))
        {
            if (channel.isOperator(sender))
            {
                channel.setTopic(command.trailer);
                channel.send(":" + sender.getPrefix() + " TOPIC " + channel.getName() + " :" + command.trailer);
            } else
                sender.send(ERR_CHANOPRIVSNEEDED(sender.getName(), channel.getName()));
        } else
            sender.send(ERR_NOTONCHANNEL(sender.getName(), channel.getName()));
    } else {
        if (channel.getTopic().size())
            sender.send(RPL_TOPIC(sender.getName(), channel.getName(), channel.getTopic()));
        else
            sender.send(RPL_NOTOPIC(sender.getName(), channel.getName()));
    }
}

void topicCommand(CommandManager::Command & command)
{
    User & sender = *command.sender;

    if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
    try
    {
        execute_topic(command, sender);
    }
    catch(Server::ChannelNotFoundException & e)
    {
        sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
    }
}