#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <poll.h>
#include <unistd.h>
#include <cstring>

#define MAX_CLIENTS 5


class Server {
public:
	Server();
	Server(int port) : port(port){};
	~Server() {};
	Server(const Server& other);
	Server& operator=(const Server& other);

	int init();

private:
	int port;
};

#endif
