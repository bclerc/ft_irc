# include "../CommandManager.hpp"

void confirm_registration(CommandManager::Command & command, User & sender)
{
	// Confirm to IRSSI client successful client registration based on IRC 2812
	sender.send(RPL_WELCOME(sender.getNick(), sender.getUserName(), sender.getServerName()));
    sender.send(RPL_YOURHOST("IRC", "1.0"));
    sender.send(RPL_CREATED("0/0/0"));
    sender.send(RPL_MYINFO(sender.getHostName(), " ", " ", " "));
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
        sender.send(ERR_NEEDMOREPARAMS("USER"));
        return ;
    }
    if (sender.isRegister())
    {
        sender.send(ERR_ALREADYREGISTRED());
        return ;
    }
	set_param(command, sender);
    sender.setStatus(User::REGISTER);
	confirm_registration(command, sender);
	return ;
}