# include "../CommandManager.hpp"

void oper(User & sender, User & target, int plus)
{
    if (sender.isOperator()) {
        target.setOperator(plus);
        sender.send(":" + sender.getName() + " MODE " + target.getName() + (plus ? " +o": " -o"));
        if (sender != target)
            target.send(":" + sender.getName() + " MODE " + target.getName() + (plus ? " +o": " -o"));
    } else
        sender.send(ERR_NOPRIVILEGES(sender.getName()));
}

void oper(User & sender, User & target, Channel & channel, int plus)
{
    if (channel.isOperator(sender)) {
		channel.setOperator(sender, plus);
        sender.send(":" + sender.getName() + " MODE " + channel.getName() + " " + target.getName() + (plus ? " +o": " -o"));
        if (sender != target)
            target.send(":" + sender.getName() + " MODE " + channel.getName() + " " + target.getName() + (plus ? " +o": " -o"));
    } else
        sender.send(ERR_CHANOPRIVSNEEDED(sender.getName(), channel.getName()));
}

void mode_channel(CommandManager::Command & command, User & sender)
{
	const char * mode = command.args[1].c_str();
	User * target = &sender;
	int		plus = 1;

	if (command.size == 2)
	{
		sender.send(":" + sender.getPrefix() + " 324 " + sender.getName() + " " + command.args[0] + " +n");
		sender.send(":" + sender.getPrefix() + " 315 " + sender.getName() + " " + command.args[0] + " :End of /WHO list.");
		return ;
	}

	if (command.args.size() == 3)
	{
		if (server.isUser(command.args[2]))
			target = &server.getUser(command.args[2]);
		else
		{
			sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[2]));
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
					sender.send(ERR_UMODEUNKNOWNFLAG(sender.getName()));
			}
    	}

	}
	else
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
}

void mode_user(CommandManager::Command & command, User & sender)
{
	const char	*mode = command.args[1].c_str();

	if (!server.isUser(command.args[0]))
    {
        sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
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
                sender.send(ERR_UMODEUNKNOWNFLAG(sender.getName()));
        }
    }
}

void modeCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	 if (command.size < 2)
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
        return ;
    }
	if (command.args[0].at(0) == '#')
		mode_channel(command, sender);
	else
		mode_user(command, sender);
	return ;
}
