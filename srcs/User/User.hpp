#ifndef USER_HPP
# define USER_HPP
# include "../../includes/Server.hpp"
# include <iostream>

# define mode_invisible 1
# define mode_receipt_notice 2;
# define mode_receive_wallops 4;
# define mode_operator 8


class Channel;

class User {

	public:

		enum Status {
			UNREGISTER,
			UNREGISTER_PASS,
			REGISTER,
			DISCONNECT,
		};


		User (void);
		User(int & fd);
		User(User const & cpy);
		~User (void);

		User & operator=(User const & rhs);

		void	setNick(std::string const nick);
		void	setUserName(std::string const username);
		void	setHostName(std::string const hostname);
		void	setServerName(std::string const servername);
		void	setRealName(std::string const realname);
		void	setStatus(Status status);
		void	setMode(const int & mode);
		void	setChannel(Channel & channel);
		void	kick (std::string const & reason);
		void	send(std::string const & request);
		void	log(std::string const message) const;

		const int			& getFd() const;
		const int			& getMode() const;
		const Status		& getStatus() const;
		const std::string 	& getNick() const;
		const std::string 	& getUserName() const;
		const std::string 	& getHostName() const;
		const std::string 	& getServerName() const;
		const std::string 	& getRealname() const;
		const std::string 	getPrefix() const;
		
		Channel				& getChannel();
		std::string			& getBuffer();

		bool isRegister(void) const;
		bool isConnected(void) const;
		

	private:
		int _fd;
		int _mode;

		Status _status;

		std::string _nick;
		std::string _username;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
		std::string _buffer;

		Channel	*	_current_channel;

};

#endif