#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>

typedef std::string string;


// RPL
string RPL_WELCOME (string nick, string user, string host);
string RPL_YOURHOST (string nick, string servername, string version);
string RPL_CREATED (string nick, string date);
string RPL_MYINFO (string nick, string servername, string version, string usermode, string channelmode);
string RPL_TOPIC (string nick, string chan_name, string chan_topic);

// ERR
string ERR_CLOSINGLINK(string nick, string user, string host, string reason);
string ERR_NEEDMOREPARAMS (string nick, string command);
string ERR_ALREADYREGISTRED (string nick);
string ERR_NONICKNAMEGIVEN (string nick);
string ERR_ERRONEUSNICKNAME (string nick, string new_nick);
string ERR_NICKNAMEINUSE (string nick, string new_nick);
string ERR_NICKCOLLISION (string nick, string new_nick);
string ERR_NOSUCHNICK (string nick, string target);
string ERR_NOPRIVILEGES (string nick);
string ERR_UMODEUNKNOWNFLAG (string nick, const char flag);
string ERR_CHANOPRIVSNEEDED (string nick, string channel);
string ERR_NOSUCHCHANNEL (string nick, string channel);




#endif