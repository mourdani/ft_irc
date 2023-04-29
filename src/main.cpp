#include <string>
#include <iostream>
#include "../includes/Server.hpp"
#include <stdlib.h>

Server *server_ptr;
void handle_sigint(int sig) {
    (void)sig;

    std::cout << std::endl << "Disconnecting clients... " << server_ptr->get_users().size() << " available" << std::endl;
    for (long unsigned int i = 0; i < server_ptr->get_users().size(); i++)
    {
        std::map<int, User *>::iterator it = server_ptr->get_users().begin();
        if (it->second->getFd() != -1)
            close(it->second->getFd());
        server_ptr->get_users().erase(it);

    }

    if (server_ptr->getSocketfd() != -1)
        close(server_ptr->getSocketfd());

    std::cout << "Exiting..." << std::endl;
    exit(0);

}


int exit_error(std::string error)
{
    std::cerr << error << std::endl;
    return (1);
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

    Server server(port, av[2]);
    server_ptr = &server;
    signal(SIGINT, handle_sigint);
    if (server.init())
		return 1;
    server.run();

    return 1;
}
