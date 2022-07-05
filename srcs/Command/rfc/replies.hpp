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
string RPL_NAMREPLY (string prefix, string nick, string chan_name, string user);
string RPL_ENDOFNAMES (string prefix, string nick, string chan_name);
string RPL_MOTDSTART (string nick);
string RPL_ENDOFMOTD (string nick);
string RPL_TOPIC (string nick, string channel, string topic);
string RPL_UMODEIS (string nick, string mode);
string RPL_NOTOPIC (string nick, string channel);
string RPL_KICK (string nick);

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
string ERR_PASSWDMISMATCH (string nick);
string RPL_YOUROPER (string nick);
string RPL_NOTONCHANNEL (string nick, string chan_name);
string ERR_CANNOTSENDTOCHAN (string nick, string channel);
string ERR_NOTONCHANNEL (string nick, string channel);
string ERR_USERNOTINCHANNEL (string nick, string channel, string user);
string ERR_CHANNELISFULL (string nick, string channel);
string ERR_UNKNOWNMODE (string nick, const char flag);
string ERR_USERSDONTMATCH(string nick);
string ERR_INVITEONLYCHAN(string nick, string channel);
string ERR_USERONCHANNEL(string nick, string target, string channel);
#endif