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
#include "colors.hpp"

#define MAX_CLIENTS 50
#define MAX_CANALS 5


class Server {
public:
	Server();
	Server(int port, std::string password) : port(port), password(password) {};
	~Server() {close(socketfd);};
	Server(const Server& other);
	Server& operator=(const Server& other);

	int init();
	void run();

	bool	user_exists(std::string nickname);
	bool 	user_exists(int fd);
	bool	canal_exists(std::string canal);
	bool	add_user(User& user);
	bool	add_canal(Canal canal);
	User*	get_user(int fd);
	Canal*	get_canal(std::string canal);


private:
	int port;
	std::string password;
	int socketfd;
	std::map<int, User> users;
	std::map<std::string, Canal> canals;
};

#endif
