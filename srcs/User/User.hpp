#ifndef USER_HPP
# define USER_HPP
# include "../../includes/Server.hpp"
# include <iostream>
 
class User {

	public:
		User(int fd);
		User(User & cpy);
		~User (void);

		User & operator=(User const & rhs);

	private:
		int _fd;

		std::string _nick;
		std::string _queue;
		User (void);

};

#endif