#include  "../CommandManager.hpp"

void	operCommand(CommandManager::Command & command)
{
	User & sender = *command.sender;

	if (command.args.size() < 2)
	{
		sender.send(ERR_NEEDMOREPARAMS(sender.getName(), command.command));
		return ;
	}
	if (command.args[0] == "admin" && command.args[1] == "admin")
	{
		sender.setOperator(true);
		sender.send(RPL_YOUROPER(sender.getName()));
	}
	else
		sender.send(ERR_PASSWDMISMATCH(sender.getName()));
	
}