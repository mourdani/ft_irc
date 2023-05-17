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
    try {
    if (ac != 3)
	throw "Usage: ./server <port> <password>";

    std::string port_str = av[1];
    if (port_str.find_first_not_of("0123456798") != std::string::npos)
	throw "Error : port incorect";

    int port = atoi(av[1]);
    if (port < 1024 || port > 65535)
        throw "Error : port outside [1024, 65535]";

    launch_server(port, av[2]);
    }

    catch (const char *e) {
	std::cerr << e << std::endl;
	return (1);
    }
    return 0;
}
