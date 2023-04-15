#include "../includes/socket.hpp"

int Server::init() {
    struct addrinfo *result;
    int socketfd;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints)); // Initialize hints struct to zero

    hints.ai_family = AF_INET6;       /* Allow IPv6 */
    hints.ai_socktype = SOCK_STREAM;  /* Stream socket */
    hints.ai_flags = AI_PASSIVE;      /* For wildcard IP address */

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
            socketfd = socket(result->ai_family,
                              result->ai_socktype,
                              result->ai_protocol);

            if (socketfd == -1) {
                result = result->ai_next; // Try next address
                continue;
            }

            if (bind(socketfd, result->ai_addr, result->ai_addrlen) == 0) {
                std::cout << "Server listening on port " << port << std::endl;
                break;
            }

            close(socketfd); // Close socket if bind fails
            result = result->ai_next; // Try next address
        }

        if (result == NULL) {
            std::cerr << "Could not bind" << std::endl;
            throw std::exception();
        }

        if (listen(socketfd, MAX_CLIENTS) < 0) {
            std::cerr << "Failed to listen" << std::endl;
            throw std::exception();
        }
    } catch (std::exception &e) {
        std::cerr << "Failed to initialize server" << std::endl;
        return 1;
    }

    struct pollfd fds[MAX_CLIENTS + 1];
    fds[0].fd = socketfd;
    fds[0].events = POLLIN;

    int new_socket;
    int i = 1;

    while (1) {
        int ret = poll(fds, MAX_CLIENTS + 1, -1);
        if (ret == -1) {
            std::cerr << "Failed to poll" << std::endl;
            break;
        }

        if (fds[0].revents & POLLIN) {
            new_socket = accept(socketfd, NULL, NULL);
            if (new_socket < 0) {
                std::cerr << "Failed to accept" << std::endl;
                break;
            }

            fds[i].fd = new_socket;
            fds[i].events = POLLIN;
            i++;
            std::cout << "New client connected " << std::endl; 
        }
        for (int j = 1; j < i; j++) {
            if (fds[j].revents & POLLIN) {
                char buffer[1024] = {0};
                int valread = recv(fds[j].fd, buffer, 1024, 0);
                if (valread == 0) {
                    std::cout << "Client disconnected : " << fds[j].fd << std::endl;
                    close(fds[j].fd);
                    fds[j].fd = -1;
                    i--;
                } else {
                    std::cout << buffer;
                }
            }
        }
        
        // Remove disconnected clients
        for (int j = 1; j < i; j++) {
            if (fds[j].fd == -1) {
                for (int k = j; k < i; k++) {
                    fds[k].fd = fds[k + 1].fd;
                }
                i--;
            }
        }


    }
    close(socketfd);
    return 0;
}


//int main() {
//    Server server(6668);
//    server.init();
//    return 0;
//}
