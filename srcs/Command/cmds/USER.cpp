# include "../CommandManager.hpp"

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
    if (sender.getStatus() >= User::REGISTER)
    {
        sender.send(ERR_ALREADYREGISTRED());
        return ;
    }

    //Need no change this
    sender.setUserName(command.args[0]);
    sender.setHostName(command.args[1]);
    sender.setServerName(command.args[2]);
    sender.setRealName(command.trailer);

    // Confirm to IRSSI client successful client registration
    sender.send(RPL_WELCOME(sender.getNick(), sender.getUserName(), sender.getServerName()));
    sender.send(RPL_YOURHOST("IRC", "1.0"));
    sender.send(RPL_CREATED("0/0/0"));
    sender.send(RPL_MYINFO(" ", " ", " ", " "));
    sender.setStatus(User::REGISTER);
}