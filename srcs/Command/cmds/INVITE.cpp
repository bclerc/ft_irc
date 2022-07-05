#include "../CommandManager.hpp"

void execute_invite(CommandManager::Command & command, User & sender)
{
    User & target = server.getUser(command.args[0]);
    Channel & channel = server.getChannel(command.args[1]);

    if (channel.isOnChannel(sender))
    {
        if (channel.isOperator(sender))
        {
            if (!channel.isOnChannel(target))
            {
                channel.invite(target);
                target.send(":" + sender.getPrefix() + " INVITE " + target.getName() + " " + channel.getName());
                sender.send(":" + sender.getPrefix() + " INVITE " + target.getName() + " " + channel.getName());
                sender.send("342 "+ sender.getName() + " " + channel.getName() + " " + target.getName());
            } else {
                sender.send(ERR_USERONCHANNEL(sender.getName(), target.getName(), channel.getName()));
            }
        } else {
            sender.send(ERR_CHANOPRIVSNEEDED(sender.getName(), channel.getName()));
        }
    } else {
        sender.send(ERR_NOTONCHANNEL(sender.getName(), channel.getName()));
    }
}

void inviteCommand(CommandManager::Command & command)
{
    User & sender = *command.sender;

    if (command.args.size() < 2)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
    try
    {
        execute_invite(command, sender);
    }
    catch(Server::ChannelNotFoundException & e)
    {
        sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
    }
    catch(Server::UserNotFoundException & e)
    {
        sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[1]));
    }
}