#ifndef ITARGET_HPP
# define ITARGET_HPP
 
# include <iostream>


class ITarget {

	public:
		
		virtual void send(std::string const & message) = 0;
		virtual const std::string & getName(void) const = 0;
		virtual ~ITarget(void) {}

};

#endif 