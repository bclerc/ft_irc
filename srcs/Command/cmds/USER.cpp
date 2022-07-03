# include "../CommandManager.hpp"

void confirm_registration(CommandManager::Command & command, User & sender)
{
	// Confirm to IRSSI client successful client registration based on IRC 2812
	sender.send(RPL_WELCOME(sender.getName(), sender.getUserName(), sender.getServerName()));
    sender.send(RPL_YOURHOST(sender.getName(), "Arago", "1.20G"));
    sender.send(RPL_MOTDSTART(sender.getName()));
    sender.send(server.getMotd(sender));
    sender.send(RPL_ENDOFMOTD(sender.getName()));
}

void set_param(CommandManager::Command & command, User & sender)
{
    sender.setUserName(command.args[0]);
    sender.setHostName(command.args[1]);
    sender.setServerName(command.args[2]);
    sender.setRealName(command.trailer);
}

void userCommand(CommandManager::Command & command)
{
    User & sender = *command.sender;
    std::vector<User>::iterator it;
    std::string realname;

    if (command.size < 5)
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getName(), "USER"));
        return ;
    }
    if (sender.isRegister())
    {
        sender.send(ERR_ALREADYREGISTRED(sender.getName()));
        return ;
    }
	set_param(command, sender);
	confirm_registration(command, sender);
    sender.setStatus(User::REGISTER);
	// c pour debug ca
    if (server.getUsers().size() == 1)
        sender.setOperator(true);
	return ;
}