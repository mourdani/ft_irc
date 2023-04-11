#include <cstring>
#include <unistd.h>



#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>

int create_socket() {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUFSIZ];

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET6;  // AD_UNSPEC;     /* Allow IPv4 or IPv6 */   
    hints.ai_socktype = SOCK_STREAM; /* Stream socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(NULL, "6667", &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            std::cout << "Socket bound to " << (rp->ai_family == AF_INET6 ? "IPv6" : "IPv4") << " address." << std::endl;
            break;                  /* Success */
        }

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);           /* No longer needed */

    if (listen(sfd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening for incoming connections..." << std::endl;

    while (1) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        int client_sockfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (client_sockfd == -1) {
            perror("accept");
            continue;
        }

        char remote_addr_str[INET6_ADDRSTRLEN];
        void *addr_ptr;
        if (peer_addr.ss_family == AF_INET) {
            addr_ptr = &((struct sockaddr_in *) &peer_addr)->sin_addr;
        } else { // AF_INET6
            addr_ptr = &((struct sockaddr_in6 *) &peer_addr)->sin6_addr;
        }
        inet_ntop(peer_addr.ss_family, addr_ptr, remote_addr_str, sizeof(remote_addr_str));
        std::cout << "Connection accepted from " << remote_addr_str << std::endl;

        close(client_sockfd);
    }

    return 0;
}

int main() {
    create_socket();
    // use "nc -6 localhost 6667" to test with ipv6
    // use "nc localhost 6667" to test with ipv4

    return 0;
}
