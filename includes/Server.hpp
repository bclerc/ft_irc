#ifndef SERVER_HPP
# define SERVER_HPP
 
# include <iostream>
# include <netinet/in.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <map>
# include <vector>


class Client;
class Channel;

class Server {

	public:

		Server(int port, std::string const & name, std::string const & password);
		Server(Server & cpy);
		~Server (void);

		Server & operator=(Server const & rhs);

		void	start(void);
		void	log (std::string const message) const;

	private:
		int 		_server_port;
		std::string _server_name;
		std::string _server_password;


		int _master_socket, _new_socket, _activity, _opt, _max_sd;
		socklen_t _addrlen;
		struct sockaddr_in _address;

		std::vector<int> _clients;
	//	std::vector<Channel> 		_channels;
	//	std::map<std::string, int> 	_clients;
		
		void	_copy_fd(std::vector<int> & clients, fd_set & readfds);

		Server (void);
	

};

#endif	