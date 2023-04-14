#include "../includes/socket.hpp"

int Server::init() {
    struct addrinfo *result;
    int socketfd;

    struct addrinfo hints;
    hints.ai_family = AF_INET6;		    /* Allow IPv6 */
    hints.ai_socktype = SOCK_STREAM;		    /* Stream socket */
    hints.ai_flags = AI_PASSIVE;		    /* For wildcard IP address */

    // port to char*
    std::stringstream ss;
    ss << port;
    std::string port_str = ss.str();
    const char *port_char = port_str.c_str();
    
    try {
    if (getaddrinfo(NULL, port_char, &hints, &result) != 0) {
	std::cerr << "Failed to get address information." << std::endl;
        throw std::exception();
    }

    while (result != NULL) {
	socketfd = socket(result->ai_family, \
		    result->ai_socktype, \
		    result->ai_protocol);

	if (socketfd == -1)
		continue;

	if (bind(socketfd, result->ai_addr, result->ai_addrlen) == 0)
	{
	    std::cout << "Server listening on port " << port << std::endl;
		break;                 
	}
	socketfd = -1;
    }

    if (result == NULL) {             
        	std::cerr << "Could not bind" << std::endl;
                throw std::exception();
    }

    if (listen(socketfd, 5) == -1) {
        std::cerr << "Failed to listen" << std::endl;
        throw std::exception();
    }
    } catch (std::exception &e) {
        std::cerr << "Failed to initialize server" << std::endl;
        return 1;
    }

    std::cout << "Listening for incoming connections..." << std::endl;


    socklen_t peer_addr_len;
    struct sockaddr_storage peer_addr;

    while (1)
    {
        peer_addr_len = sizeof(struct sockaddr_storage);
        int client_sockfd = accept(socketfd, (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (client_sockfd == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }
        std::cout << "Connection accepted from " << inet_ntoa(((struct sockaddr_in *)&peer_addr)->sin_addr) << std::endl;
    }
    //freeaddrinfo(result);
    return 0;

}

//int main() {
//    Server server("6667");
//    server.init();
//    return 0;
//}
