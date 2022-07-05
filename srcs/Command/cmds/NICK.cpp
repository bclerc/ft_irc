# include	"../CommandManager.hpp"
# include	<cctype>

int	check_nickname(std::string const & nick)
{
	const char special_char[11] = "-[]\\`^{}_ ";

	if (nick.size() < 3 || nick.size() > 20)
		return (0);
	for (unsigned int i = 0; i < nick.size(); i++)
	{
		if (!std::isalnum(nick[i])
				&& nick.find_first_of(special_char) == std::string::npos)
			return 0;
	}
	return 1;
}

void nickCommand(CommandManager::Command & command)
{
	if (command.size < 2)
	{
		command.sender->send(ERR_NONICKNAMEGIVEN(command.sender->getName()));
		return ;
	}
	if (server.isUser(command.args[0]))
	{
		command.sender->send(ERR_NICKNAMEINUSE(command.sender->getName(), command.args[0]));
		return;
	}
	if (!check_nickname(command.args[0]))
	{
		command.sender->send(ERR_ERRONEUSNICKNAME(command.sender->getName(), command.args[0]));
		return ;
	}
	command.sender->setNick(command.args[0]);
	return ;
}