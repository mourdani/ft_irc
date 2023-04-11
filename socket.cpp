#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

class Endpoint {
public:
    Endpoint(const std::string& ip, int port) : ip(ip), port(port) {}
    std::string ipv6;
    std::string ip;
    int port;
};
int socket_ipv4() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
		std::cerr << "Failed to create socket: " << std::endl;
		return 1;
	}

    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sin_port = htons(6667);

    if (bind(sockfd, (struct sockaddr*)&sock, sizeof(sock)) == -1) {
    std::cerr << "Failed to bind socket: " << std::endl;
    return 1;
    }
    
    std::cout << "Socket bound to " << inet_ntoa(sock.sin_addr) << ":" << ntohs(sock.sin_port) << std::endl;
    
    listen(sockfd, 5); // listen for incoming connections
    std::cout << "Listening for incoming connections..." << std::endl;
    select(sockfd, NULL, NULL, NULL, NULL); // wait for incoming connections
    struct sockaddr_in remote_addr;
    socklen_t remote_addr_len = sizeof(remote_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr*)&remote_addr, &remote_addr_len);
    if (client_sockfd == -1) {
    	std::cerr << "Failed to accept connection: " << std::endl;
    	return 1;
    }
    
    std::cout << "Connection accepted from " << inet_ntoa(remote_addr.sin_addr) << ":" << ntohs(remote_addr.sin_port) << std::endl;
    
    return 0;
}

int socket_ipv6() {
    int sock6fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock6fd == -1) {
        std::cerr << "Failed to create socket: " << std::endl;
        return 1;
    }

    
    struct sockaddr_in6 sock6;
    sock6.sin6_family = AF_INET6;
    sock6.sin6_addr = IN6ADDR_ANY_INIT;// any local address
    sock6.sin6_port = htons(6667); // local port for TCP

    if (bind(sock6fd, (struct sockaddr*)&sock6, sizeof(sock6)) == -1) {
		std::cerr << "Failed to bind socket: " << std::endl;
		return 1;
    }
    std::cout << "Socket bound to " << inet_ntop(AF_INET6, &sock6.sin6_addr, NULL, 0) << ":" << ntohs(sock6.sin6_port) << std::endl;
//
//    listen(sock6fd, 5); // listen for incoming connections
//    // wait for incoming connections
//    std::cout << "Listening for incoming connections..." << std::endl;
//    select(sock6fd, NULL, NULL, NULL, NULL);
//    struct sockaddr_in6 remote_addr;
//    socklen_t remote_addr_len = sizeof(remote_addr);
//    int client_sockfd = accept(sock6fd, (struct sockaddr*)&remote_addr, &remote_addr_len);
//    if (client_sockfd == -1) {
//	    std::cerr << "Failed to accept connection: " << std::endl;
//	    return 1;
//	}
//    // connection accepted
//    std::cout << "Connection accepted from " << inet_ntop(AF_INET6, &remote_addr.sin6_addr, NULL, 0) << ":" << ntohs(remote_addr.sin6_port) << std::endl;
//
    return 0;
}

int main() {
    socket_ipv4();
    return 0;
}

