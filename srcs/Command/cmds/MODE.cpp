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
    if (sender.isOperator()) {
        channel.setOperator(target);
        sender.send(":" + sender.getNick() + " MODE " + target.getNick() + (plus ? " +o": " -o"));
        if (sender != target)
            target.send(":" + sender.getNick() + " MODE " + target.getNick() + (plus ? " +o": " -o"));
    } else
        sender.send(ERR_NOPRIVILEGES(sender.getNick()));
}

void mode_channel(CommandManager::Command & command, User & sender)
{
	const char * mode = command.args[1].c_str();
	User * target = &sender;
	int		plus;

	if (command.args.size() == 4)
	std::cout << "Args: " << command.args[2]  << "Size : " << command.size << std::endl;
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
					sender.send(ERR_UMODEUNKNOWNFLAG(sender.getNick()));
			}
    	}

	}
	else
	{

	std::cout << " Nop Channnel pas la " << std::endl;
	}
	//erreur si c pas un channel ici
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
	int			plus = 0;

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
                sender.send(ERR_UMODEUNKNOWNFLAG(sender.getNick()));
        }
    }
}

void modeCommand(CommandManager::Command & command)
{
    int    plus = 1;

    User & sender = *command.sender;

    if (command.size <= 2)
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getNick(), command.command));
        return ;
    }

	std::cout << command.args[0].at(0) << " ///////////////////// ICI "  << command.args[0] << std::endl;
	if (command.args[0].at(0) == '#')
		mode_channel(command, sender);
	else
		mode_user(command, sender);
	return ;
}