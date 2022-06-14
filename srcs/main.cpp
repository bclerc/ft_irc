/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 03:41:19 by bclerc            #+#    #+#             */
/*   Updated: 2022/06/14 00:16:49 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server server;

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	server = Server(std::atoi(argv[1]), std::string("IrcServ"), std::string(argv[2]));
	server.start();

    return (0);
}