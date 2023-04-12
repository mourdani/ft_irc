
#include <string>
#include <iostream>
#include "../includes/data.hpp"
#include "socket.hpp"
#include <stdlib.h>

int exit_error(std::string error)
{
    std::cerr << error << std::endl;
    return (1);
}

int main(int ac, char **av) {
    if (ac != 3)
        return exit_error("Usage : ircserv <port> <password>");

    irc_data data;

    std::string port_str = av[1];

    if (port_str.find_first_not_of("0123456798") != std::string::npos)
        return exit_error("Error : port incorect");

    int port = atoi(av[1]);

    if (port <= 0 || port > 65535)
        return exit_error("Error : port outside [0, 65535]");

    data.password = av[2];
    data.port = port;

    Server server(6667);
    server.init();

    return 1;
}