# include "../CommandManager.hpp"

void vanish(User & sender, User & target)
{
    std::cout << sender.getNick() << " Vanished " << target.getNick() << std::endl; 
}

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

void modeCommand(CommandManager::Command & command)
{
    int    plus = 1;

    User & sender = *command.sender;

    if (command.size <= 2)
    {
        sender.send(ERR_NEEDMOREPARAMS(sender.getNick(), command.command));
        return ;
    }
    if (!server.isUser(command.args[0]))
    {
        sender.send(ERR_NOSUCHNICK(sender.getNick(), command.args[0]));
        return ;
    }

    User & target = server.getUser(command.args[0]);
    const char * mode = command.args[1].c_str();

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
            case 'i':                           // a gerer ??
                vanish(sender, target);
                break;
            default:
                sender.send(ERR_UMODEUNKNOWNFLAG(sender.getNick()));
        }
    }
}