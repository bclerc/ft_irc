# include "../CommandManager.hpp"

void joinCommand(CommandManager::Command & command)
{
  server.getChannel(command.args[0])
}