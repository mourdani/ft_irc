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
#include <vector>
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
	User*	get_user(std::string nickname);
	Canal*	get_canal(std::string canal);

	int handle_command(User& user, char *buf);
	int	quit(User& user, std::vector<std::string> args);
	int	nick(User& user, std::vector<std::string> args);
	int	join(User& user, std::vector<std::string> args);
	int	part(User& user, std::vector<std::string> args);


private:
	int port;
	std::string password;
	int socketfd;
	std::map<int, User> users;
	std::map<std::string, int> _user_ids;
	std::map<std::string, Canal> canals;
};

typedef	int (Server::*command)(User& user, std::vector<std::string> args);

#endif
