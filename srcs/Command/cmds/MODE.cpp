# include "../CommandManager.hpp"

void user_mode(CommandManager::Command const & command, User & sender)
{
	User & target = server.getUser(command.args[0]);
	if (command.size < 2)
	{
		if (sender.getName() != target.getName())
		{
			sender.send(RPL_UMODEIS(target.getName(), target.isOperator() ? "+o" : ""));
			target.send(RPL_UMODEIS(target.getName(), target.isOperator() ? "+o" : ""));
			return ;
		}
		sender.send(ERR_USERSDONTMATCH(sender.getName()));
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
	if (command.size < 2)
	{
		sender.send("324 " + sender.getName() + " " + channel.getName() + " +n");
		return ;
	}

	User & target = command.size == 3 ? server.getUser(command.args[2]) : sender;
	if (sender.isOperator())
	{
		if (command.args[1] == "+o")
			channel.setOperator(target, true);
		else if (command.args[1] == "-o")
			channel.setOperator(target, false);
		else {
			sender.send(ERR_UMODEUNKNOWNFLAG(sender.getName(), command.args[1].c_str()[0]));
			return ;
		}

		target.send(": " + sender.getName() + " MODE " + channel.getName() + " " + command.args[1] + " " + target.getName());
		if (sender != target)
			sender.send(": " + sender.getName() + " MODE " + channel.getName() + " " + command.args[1] + " " + target.getName());
	}
}

void modeCommmnad(CommandManager::Command const & command)
{
	User & sender = *command.sender;
	if (command.args.size() < 1)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	if (command.args[0][1] == '#')
		channel_mode(command, sender);
	else
		user_mode(command, sender);
}