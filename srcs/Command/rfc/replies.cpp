# include "replies.hpp"

/**
* @todo
* Changer le caractere "*" par un userprefix
* Un user prefix
* et je ne sais d'autres reponses de la rfc
* et peut-etre mettre les noms en minuscule 
*/

// RPL
string RPL_WELCOME (string nick, string user, string host)
{ return ("001 "+ nick +" :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host); }

string RPL_YOURHOST (string nick, string servername, string version)
{ return ("002 "+ nick + " Your host is " + servername + ", running version " + version); }

string RPL_CREATED (string nick, string date)
{ return ("003 "+ nick + " This server was created " + date); }

string RPL_MYINFO (string nick, string servername, string version, string usermode, string channelmode)
{ return ("004 "+ nick + " " + servername + " " + version + " " + usermode + " " + channelmode); }

// ERR
string ERR_CLOSINGLINK(string nick, string user, string host, string reason)
{ return ("ERROR :Closing link: (" + user + "@" + host + ") [" + reason + "]"); }

string ERR_NEEDMOREPARAMS(string nick, string command)
{ return ("461 "+ nick + " " + command + " :Not enough parameters"); }

string ERR_ALREADYREGISTRED (string nick)
{ return ("462 "+ nick + " :Unauthorized command (already registered)"); }

string ERR_NONICKNAMEGIVEN (string nick)
{ return ("431 "+ nick + " :No nickname given"); }

string ERR_ERRONEUSNICKNAME (string nick, string new_snick)
{ return ("462 "+ nick + " " + nick + " :Erroneus nickname" ); }

string ERR_NICKNAMEINUSE (string nick, string new_nick)
{ return ("433 "+ nick + " " + nick + " :Nickname is already in use"); }

string ERR_NICKCOLLISION (string nick, string new_nick)
{ return ("436 "+ nick + " " + nick + " :Nickname collision KILL");}