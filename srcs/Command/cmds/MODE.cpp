# include "../CommandManager.hpp"

void user_mode(CommandManager::Command const & command, User & sender)
{
	User & target = server.getUser(command.args[0]);
	if (command.size < 3)
	{
		if (sender != target)
		{
			sender.send(ERR_USERSDONTMATCH(sender.getName()));
			return ;
		}
		sender.send(RPL_UMODEIS(target.getName(), target.isOperator() ? "+o" : ""));
		return ;
	}
	if (sender.isOperator())
	{
		if (command.args[1] == "+o")
			target.setOperator(true);
		else if (command.args[1] == "-o")
			target.setOperator(false);
		else {
			sender.send(ERR_UMODEUNKNOWNFLAG(sender.getName(), command.args[1].c_str()[0]));
			return ;
		}
		if (target != sender)
			sender.send(":" + target.getPrefix() + " MODE " + target.getName() + " " + command.args[1]);
		target.send(":" + target.getPrefix() + " MODE " + target.getName() + " " + command.args[1]);
	}
	else
		sender.send(ERR_NOPRIVILEGES(sender.getName()));
}

void channel_mode(CommandManager::Command const & command, User & sender)
{
	Channel & channel = server.getChannel(command.args[0]);
	std::string			mode;
	int					type = 0;
	char				c;

	if (command.size < 3)
	{
		sender.send("324 " + sender.getName() + " " + channel.getName() + " +n");
		return ;
	}
	User & target = command.size == 2 ? server.getUser(command.args[2]) : sender;
	
	if (channel.isOperator(sender))
	{
		for (int i = 0; (c = command.args[1][i]); i++)
		{
			if (c == '+' || c == '-')
			{
			}
			switch (c) {
				case '+':
				case '-':
					type = (c == '+');
					mode =+c;
					break ;
				case 'o':
					channel.setOperator(target, type);
					mode+= c;
					break;
				case 'i':
					channel.setInviteOnly(type);
					mode+= c;
					break ;
				default:
					sender.send(ERR_UMODEUNKNOWNFLAG(sender.getName(), c));
			}
		}
		target.send(":" + sender.getName() + " MODE " + channel.getName() + " " + mode + " " + target.getName());
		if (sender != target)
			sender.send(":" + sender.getName() + " MODE " + channel.getName() + " " + mode + " " + target.getName());
	} else {
		sender.send(ERR_CHANOPRIVSNEEDED(sender.getName(), channel.getName()));
	}
}

void modeCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;
	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	try
	{
		if (command.args[0][0] == '#')
			channel_mode(command, sender);
		else
			user_mode(command, sender);
	} catch (Server::UserNotFoundException & e) {
		sender.send(ERR_NOSUCHNICK(sender.getName(), command.args[0]));
	} catch (Server::ChannelNotFoundException & e) {
		sender.send(ERR_NOSUCHCHANNEL(sender.getName(), command.args[0]));
	}
}

