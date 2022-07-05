# include "replies.hpp"

// RPL
string RPL_WELCOME (string nick, string user, string host)
{ return ("001 "+ nick +" :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host); }

string RPL_YOURHOST (string nick, string servername, string version)
{ return ("002 "+ nick + " Your host is " + servername + ", running version " + version); }

string RPL_CREATED (string nick, string date)
{ return ("003 "+ nick + " This server was created " + date); }

string RPL_MYINFO (string nick, string servername, string version, string usermode, string channelmode)
{ return ("004 "+ nick + " " + servername + " " + version + " " + usermode + " " + channelmode); }

string RPL_NAMREPLY (string prefix, string nick, string chan_name, string user)
{ return (":" + prefix + " 353 " + nick + " = " + chan_name + " :" + user); }

string RPL_ENDOFNAMES (string prefix, string nick, string chan_name)
{ return (":" + prefix + " 366 " + nick + " " + chan_name + " :End of /NAMES list"); }

string RPL_YOUROPER (string nick)
{ return ("381 " + nick + " :You are now an IRC operator"); }

string RPL_NOTONCHANNEL (string nick, string chan_name)
{ return ("442 " + nick + " " + chan_name + " :You are not on that channel"); }

string RPL_MOTDSTART (string nick)
{ return ("375 " + nick + " :- Arago Message of the day -"); }

string RPL_ENDOFMOTD (string nick)
{ return ("376 " + nick + " :End of MOTD"); }


// ERR
string ERR_CLOSINGLINK(string user, string host, string reason)
{ return ("ERROR :Closing link: (" + user + "@" + host + ") [" + reason + "]"); }

string ERR_NEEDMOREPARAMS(string nick, string command)
{ return ("461 "+ nick + " " + command + " :Not enough parameters"); }

string ERR_ALREADYREGISTRED (string nick)
{ return ("462 "+ nick + " :Unauthorized command (already registered)"); }

string ERR_NONICKNAMEGIVEN (string nick)
{ return ("431 "+ nick + " :No nickname given"); }

string ERR_ERRONEUSNICKNAME (string nick, string new_nick)
{ return ("462 "+ nick + " " + new_nick + " :Erroneus nickname" ); }

string ERR_NICKNAMEINUSE (string nick, string new_nick)
{ return ("433 "+ nick + " " + new_nick + " :Nickname is already in use"); }

string ERR_NICKCOLLISION (string nick)
{ return ("436 "+ nick + " " + nick + " :Nickname collision KILL");}

string ERR_NOSUCHNICK (string nick, string target)
{ return ("401 "+ nick + " " + target + " :No such nick/channel"); }

string ERR_NOPRIVILEGES (string nick)
{ return ("481 " + nick + " :Permission Denied - You're not an IRC operator"); }

string ERR_CHANOPRIVSNEEDED (string nick, string channel)
{ return ("482 " + nick + " " + channel + " :Permission Denied - You're not an IRC operator"); }

string ERR_NOSUCHCHANNEL (string nick, string channel)
{ return ("403 " + nick + " " + channel + " :No such channel"); }

string ERR_UMODEUNKNOWNFLAG (string nick, const char flag)

{ return ("501 " + nick + " :" + flag + " Unkown MODE flag"); }

string ERR_PASSWDMISMATCH (string nick)
{ return ("464 " + nick + " :Password incorrect"); }

string ERR_CANNOTSENDTOCHAN (string nick, string channel)
{ return ("404 " + nick + " " + channel + " :Cannot send to channel"); }

string ERR_NOTONCHANNEL (string nick, string channel)
{ return ("442 " + nick + " " + channel + " :You're not on that channel"); }

string ERR_USERNOTINCHANNEL (string nick, string channel, string user)
{ return ("441 " + nick + " " +user + " " + channel + " :They aren't on that channel"); }

string ERR_CHANNELISFULL (string nick, string channel)
{
    return ("471 " + nick + " " + channel + " :Cannot join channel (Is full)");
}

string ERR_USERSDONTMATCH(string nick)
{
	return ("502 " + nick + " :Cannot change mode for other users");
}

string RPL_UMODEIS (string nick, string mode)
{ return ("221 " + nick + " :" + mode); }
