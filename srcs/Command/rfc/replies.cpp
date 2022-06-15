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
{ return ("001 * Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host); }

string RPL_YOURHOST (string servername, string version)
{ return ("002 * Your host is " + servername + ", running version " + version); }

string RPL_CREATED (string date)
{ return ("003 * This server was created " + date); }

string RPL_MYINFO (string servername, string version, string usermode, string channelmode)
{ return ("004 * " + servername + " " + version + " " + usermode + " " + channelmode); }

// ERR
string ERR_CLOSINGLINK(string user, string host, string reason)
{ return ("ERROR :Closing link: (" + user + "@" + host + ") [" + reason + "]"); }

string ERR_NEEDMOREPARAMS(string command)
{ return ("461 * " + command + " :Not enough parameters"); }

string ERR_ALREADYREGISTRED (void)
{ return ("462 * :Unauthorized command (already registered)"); }

string ERR_NONICKNAMEGIVEN (void)
{ return ("431 * :No nickname given"); }

string ERR_ERRONEUSNICKNAME (string nick)
{ return ("462 * " + nick + " :Erroneus nickname" ); }

string ERR_NICKNAMEINUSE (string nick)
{ return ("433 * " + nick + " :Nickname is already in use"); }

string ERR_NICKCOLLISION (string nick)
{ return ("436 * " + nick + " :Nickname collision KILL");}