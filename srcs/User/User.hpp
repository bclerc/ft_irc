#ifndef USER_HPP
# define USER_HPP
# include "../../includes/Server.hpp"
# include <iostream>
 


class User {

	enum class Status {
		UNREGISTER = 0,
		REGISTER = 1,
	};

	public:
		User(int & fd);
		User(User const & cpy);
		~User (void);

		User & operator=(User const & rhs);

		void	setNick(std::string const & nick);

		const int			getFd() const;
		const Status	&	getStatus() const;
		const std::string & getNick() const;

	private:
		int _fd;

		Status _status;

		std::string _nick;
		std::string _queue;

		User (void);

};

#endif