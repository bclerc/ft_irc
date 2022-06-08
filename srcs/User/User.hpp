#ifndef USER_HPP
# define USER_HPP
# include "../../includes/Server.hpp"
# include <iostream>
 


class User {

	public:

		enum Status {
			UNREGISTER,
			REGISTER,
			DISCONNECT,
		};

		User (void);
		User(int & fd);
		User(User const & cpy);
		~User (void);

		User & operator=(User const & rhs);

		void	setNick(std::string const & nick);
		void	setStatus(Status status);

		void	send(std::string const & request);
		void	log(std::string const message) const;
		const int			getFd() const;
		const Status	&	getStatus() const;
		const std::string & getNick() const;

		std::string & getBuffer();

	private:
		int _fd;

		Status _status;

		std::string _nick;
		std::string _buffer;


};

#endif