#ifndef SERVER_HPP
# define SERVER_HPP
 
# include <iostream>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/socket.h>

class Server {

	public:

		Server(int port, std::string const & name, std::string const & password);
		Server(Server & cpy);
		~Server (void);

		Server & operator=(Server const & rhs);

		void	start(void) const;
		void	log (std::string const message) const;

	private:
		std::string _server_name;
		int 		_server_port;
		std::string _server_password;

		Server (void);
	

};

#endif	