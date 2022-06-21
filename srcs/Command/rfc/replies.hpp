#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>

typedef std::string string;


// RPL
string RPL_WELCOME (string nick, string user, string host);
string RPL_YOURHOST (string nick, string servername, string version);
string RPL_CREATED (string nick, string date);
string RPL_MYINFO (string nick, string servername, string version, string usermode, string channelmode);

// ERR
string ERR_CLOSINGLINK(string nick, string user, string host, string reason);
string ERR_NEEDMOREPARAMS (string nick, string command);
string ERR_ALREADYREGISTRED (string nick);
string ERR_NONICKNAMEGIVEN (string nick);
string ERR_ERRONEUSNICKNAME (string nick, string new_nick);
string ERR_NICKNAMEINUSE (string nick, string new_nick);
string ERR_NICKCOLLISION (string nick, string new_nick);

#endif