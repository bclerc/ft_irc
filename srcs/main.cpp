/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 03:41:19 by bclerc            #+#    #+#             */
/*   Updated: 2022/07/05 14:28:27 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <signal.h>

Server server;

void signalhandler(int signum)
{
	if (signum == SIGINT)
		server.shutdown();
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	server = Server(std::atoi(argv[1]), std::string("IrcServ"), std::string(argv[2]), 100);
	signal(SIGINT, signalhandler);
	server.start();

    return (0);
}