#ifndef SERVER_HPP
# define SERVER_HPP
 
# include "ITarget.hpp"
# include "../srcs/Command/CommandManager.hpp"
# include "../srcs/User/User.hpp"
# include "../srcs/Channel/Channel.hpp"



# include <iostream>
# include <cstring>
# include <netinet/in.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <map>
# include <vector>
# include <errno.h>
# include <time.h> 

class User;
class Channel;
class CommandManager;

typedef std::vector<User*>::iterator iterator;
typedef std::vector<User*>::const_iterator const_iterator;
typedef std::map<std::string, Channel*>::iterator channel_iterator;
typedef std::map<std::string, Channel*>::const_iterator const_channel_iterator;

class Server {

	public:

		Server (void);
		Server(int port, std::string const & name, std::string const & password);
		Server(Server & cpy);
		~Server (void);

		Server & operator=(Server const & rhs);

		void	start(void);
		void    shutdown(void);
		void	log (std::string const message) const;
		void	send_all(void);
		void	kickAll(std::string const & reason);
		
		const std::string 		&	getPass() const; 
		const std::vector<User*> &	getUsers() const;
		const std::map<std::string, Channel*> & getChannelMap(void) const;

		bool	isUser(std::string const & name);
		bool	isChannel(std::string const & name);
		
		User & getUser(std::string const & name);

		Channel	& createChannel(std::string const & name, User & owner);
		Channel & getChannel(std::string const & name);
		
		ITarget & getTarget(std::string const & name);

	private:

		int 		_server_port;
		std::string _server_name;
		std::string _server_password;

		int _master_socket, _new_socket, _activity, _opt, _max_sd;
		socklen_t _addrlen;
		struct sockaddr_in _address;

		std::vector<User*> _users;
		std::map<std::string, Channel *>  _channels;		

		void	_run(fd_set & readfds);
		void 	_accept_connection(fd_set & readfds);
		void	_copy_fd(std::vector<User*> & users, fd_set & readfds);
		void 	_get_requests(fd_set & readfds, CommandManager & commandManager);
		void	_remove_disconnect();

	public:
	
		class UserNotFoundException : public std::exception {
			public:
				virtual const char * what() const throw();
		};

		class ChannelNotFoundException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
};

extern Server server;

#endif	