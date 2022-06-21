# include "../CommandManager.hpp"

void modeCommand(CommandManager::Command & command)
{
    User & sender = *command.sender;
    User & target = server.getUser(command.args[0]);

}