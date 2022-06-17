#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>

typedef std::string string;


// RPL
string RPL_WELCOME (string nick, string user, string host);
string RPL_YOURHOST (string servername, string version);
string RPL_CREATED (string date);
string RPL_MYINFO (string servername, string version, string usermode, string channelmode);

// ERR
string ERR_CLOSINGLINK(string user, string host, string reason);
string ERR_NEEDMOREPARAMS (string command);
string ERR_ALREADYREGISTRED (void);
string ERR_NONICKNAMEGIVEN (void);
string ERR_ERRONEUSNICKNAME (string nick);
string ERR_NICKNAMEINUSE (string nick);
string ERR_NICKCOLLISION (string nick);

#endif