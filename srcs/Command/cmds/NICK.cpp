# include "../CommandManager.hpp"

void nickCommand(CommandManager & command, std::vector<std::string> & args)
{
	User & sender = command.getSender();

	sender.setNick(args[1]);
	sender.log(("Change nickname to ") + args[1]);
	sender.send("{RI");
	return ;
}