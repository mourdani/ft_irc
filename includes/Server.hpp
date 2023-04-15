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
#include <string>
#include <map>
#include "User.hpp"
#include "Canal.hpp"

#define MAX_CLIENTS 5


class Server {
public:
	Server();
	Server(int port) : port(port){};
	~Server() {close(socketfd);};
	Server(const Server& other);
	Server& operator=(const Server& other);

	void init();
	void run();

	bool	user_exists(std::string nickname);
	bool	canal_exists(std::string canal);
	bool	add_user(User user);
	bool	add_canal(Canal canal);
	User*	get_user(std::string hostname);
	Canal*	get_canal(std::string canal);

private:
	int port;
	int password;
	int socketfd;
	std::map<std::string, User> users;
    	std::map<std::string, Canal> canals;
};

#endif
