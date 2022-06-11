#ifndef SERVER_HPP
# define SERVER_HPP
 
# include "../srcs/Command/CommandManager.hpp"
# include "../srcs/User/User.hpp"

# include <iostream>
# include <cstring>
# include <netinet/in.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <map>
# include <vector>

class User;
class CommandManager;
class Server {

	public:
		typedef std::vector<User>::iterator iterator;

		Server(int port, std::string const & name, std::string const & password);
		Server(Server & cpy);
		~Server (void);

		Server & operator=(Server const & rhs);

		void	start(void);
		void	log (std::string const message) const;
		void	send_all(void);
	
	private:

		int 		_server_port;
		std::string _server_name;
		std::string _server_password;

		int _master_socket, _new_socket, _activity, _opt, _max_sd;
		socklen_t _addrlen;
		struct sockaddr_in _address;

		std::vector<User> _users;
		

		void	_run(fd_set & readfds);
		void 	_accept_connection(fd_set & readfds);
		void	_copy_fd(std::vector<User> & users, fd_set & readfds);
		void 	_get_requests(fd_set & readfds, CommandManager & commandManager);
		void	_remove_disconnect();
		Server (void);
	

};

#endif	