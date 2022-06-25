# include "../CommandManager.hpp"

void oper(User & sender, User & target, int plus)
{
    if (sender.isOperator()) {
        target.setOperator(plus);
        sender.send(":" + sender.getNick() + " MODE " + target.getNick() + (plus ? " +o": " -o"));
        if (sender != target)
            target.send(":" + sender.getNick() + " MODE " + target.getNick() + (plus ? " +o": " -o"));
    } else
        sender.send(ERR_NOPRIVILEGES(sender.getNick()));
}

void oper(User & sender, User & target, Channel & channel, int plus)
{
    if (channel.isOperator(sender)) {
		channel.setOperator(sender, plus);
        sender.send(":" + sender.getNick() + " MODE " + channel.getName() + " " + target.getNick() + (plus ? " +o": " -o"));
        if (sender != target)
            target.send(":" + sender.getNick() + " MODE " + channel.getName() + " " + target.getNick() + (plus ? " +o": " -o"));
    } else
        sender.send(ERR_CHANOPRIVSNEEDED(sender.getNick(), channel.getName()));
}

void mode_channel(CommandManager::Command & command, User & sender)
{
	const char * mode = command.args[1].c_str();
	User * target = &sender;
	int		plus = 1;

	if (command.args.size() == 3)
	{
		if (server.isUser(command.args[2]))
			target = &server.getUser(command.args[2]);
		else
		{
			sender.send(ERR_NOSUCHNICK(sender.getNick(), command.args[2]));
			return ;
		}
	}
	if (server.isChannel(command.args[0]))
	{
		Channel & channel = server.getChannel(command.args[0]);
	   
	    for (int i = 0; mode[i]; i++)
    	{
			switch (mode[i])
			{
				case '+':
					plus = 1;
					break ;
				case '-':
					plus = 0;
					break ;
				case 'o':
					oper(sender, *target, channel, plus);
					break;
				default:
					sender.send(ERR_UMODEUNKNOWNFLAG(sender.getNick(), mode[i]));
			}
    	}

	}
	else
		sender.send(ERR_NOSUCHCHANNEL(sender.getNick(), command.args[0]));
}

void mode_user(CommandManager::Command & command, User & sender)
{
	const char	*mode = command.args[1].c_str();

	if (!server.isUser(command.args[0]))
    {
        sender.send(ERR_NOSUCHNICK(sender.getNick(), command.args[0]));
        return ;
    }

	User		&target = server.getUser(command.args[0]);
	int			plus = 1;

    for (int i = 0; mode[i]; i++)
    {
        switch (mode[i])
        {
            case '+':
                plus = 1;
                break ;
            case '-':
                plus = 0;
                break ;
            case 'o':
                oper(sender, target, plus);
                break;
            default:
                sender.send(ERR_UMODEUNKNOWNFLAG(sender.getNick(), mode[i]));
        }
    }
}

void modeCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	 if (command.size <= 2)
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getNick(), command.command));
        return ;
    }
	if (command.args[0].at(0) == '#')
		mode_channel(command, sender);
	else
		mode_user(command, sender);
	return ;
}