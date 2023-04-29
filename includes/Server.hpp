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
#include <csignal>

#define MAX_CLIENTS 50
#define MAX_CANALS 5

std::vector<std::string>	split(std::string str, char delimiter);
void handle_sigint(int sig);

class Server {
public:
	Server();
	Server(int port, std::string password) : port(port), password(password), _name("42_FTIRC") {};
	~Server();
	Server(const Server& other);
	Server& operator=(const Server& other);


	int init();
	void run();

	bool	user_exists(std::string nickname);
	bool 	user_exists(int fd);
	bool	canal_exists(std::string canal);
	bool	add_user(User *user);
	bool	add_canal(Canal *canal);
	User*	get_user(int fd);
	User*	get_user(std::string nickname);
	Canal*	get_canal(std::string canal);
	int	getSocketfd() const { return socketfd; }
	int	get_port() const;

	std::map<int, User *>	get_users() const;
	

	int	handle_command(User *user, char *buf);
	std::string	command_reply(int code, std::string reply) const;

	int	join(User *user, std::vector<std::string> args);
	int	nick(User *user, std::vector<std::string> args);
	int	user(User *user, std::vector<std::string> args);
	int	part(User *user, std::vector<std::string> args);
	int	list(User *user, std::vector<std::string> args);
	int	privmsg(User *user, std::vector<std::string> args);
	int	quit(User *user, std::vector<std::string> args);
	int	ping(User *user, std::vector<std::string> args);
	int	names(User *user, std::vector<std::string> args);

	//get name
	std::string get_name() const;

private:
	int port;
	std::string password;
	int socketfd;
	std::string _name;
	std::map<int, User *> users;
	std::map<std::string, int> _user_ids;
	std::map<std::string, Canal *> canals;
};

typedef	int (Server::*command)(User *user, std::vector<std::string> args);

#endif
