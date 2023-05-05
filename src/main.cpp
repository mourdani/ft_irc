#include <string>
#include <iostream>
#include "../includes/Server.hpp"
#include <stdlib.h>

Server *server_ptr;

void handle_sigint(int sig) {
    (void)sig;

    server_ptr->~Server();
    std::cout << std::endl << "Server closed" << std::endl;
    exit(0);

}


int exit_error(std::string error)
{
    std::cerr << error << std::endl;
    return (1);
}

int	launch_server(int port, char *pw)
{
    Server server(port, pw);
    server_ptr = &server;
    signal(SIGINT, handle_sigint);
    if (server.run())
	return (1);
    return (0);
}

int main(int ac, char **av) {
    if (ac != 3)
        return exit_error("Usage : ircserv <port> <password>");


    std::string port_str = av[1];

    if (port_str.find_first_not_of("0123456798") != std::string::npos)
        return exit_error("Error : port incorect");

    int port = atoi(av[1]);
	if (port <= 0 || port > 65535)
		return exit_error("Error : port outside [0, 65535]");

    if (launch_server(port, av[2]))
		return (1);
    return 0;
}
