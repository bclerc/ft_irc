#ifndef USER_HPP
# define USER_HPP
# include "../../includes/Server.hpp"
# include <iostream>
# include <sstream>

class Channel;

class User : public ITarget {

	public:
		std::string receive_buffer;

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
		bool operator==(const User & rhs);
		bool operator!=(const User & rhs);


		void	setNick(std::string const nick);
		void	setUserName(std::string const username);
		void	setHostName(std::string const hostname);
		void	setServerName(std::string const servername);
		void	setRealName(std::string const realname);
		void	setStatus(Status status);
		void	setChannel(Channel & channel);
		void	setChannel(Channel * channel);
		void	setOperator(bool value);
		void	removeChannel(Channel * channel);
		void	kick ();
		void	kill ();
		void	send(std::string const & request);
		void	sendToChannels(std::string const & request);
		void	sendWithOut(std::string const & request, ITarget & out);
		void	log(std::string const message) const;
		void	addChannelList(Channel &chanel);


		const int			& getFd() const;
		const Status		& getStatus() const;
		const std::string 	& getName() const;
		const std::string 	& getUserName() const;
		const std::string 	& getHostName() const;
		const std::string 	& getServerName() const;
		const std::string 	& getRealname() const;
		const std::string 	 getPrefix() const;

		std::string			& getBuffer();

		bool isRegister(void)	const;
		bool isConnected(void)	const;
		bool isOperator(void)	const;
		bool isOnChannel(void)	const;
		bool isOnChannel(std::string const & Channel)	const;

	private:
		int _fd;
		int _mode;
		
		bool _operator;

		Status _status;

		std::string _nick;
		std::string _username;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
		std::string _buffer;

		
		std::vector<Channel	*>	_current_channel;

};


#endif