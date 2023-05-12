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
#include "errorCodes.hpp"

#define MAX_CLIENTS 50
#define MAX_CANALS 5

std::vector<std::string>	split(std::string str, char delimiter);
void handle_sigint(int sig);

#define QUIT 2
#define DIE 3
#define BAD_USER 4

class Server;

typedef	int (Server::*command)(User *user, std::vector<std::string> args);

class Server {
public:
	Server(int port, std::string password);
	~Server();
	Server(const Server& other);
	Server& operator=(const Server& other);

	int init();
	int run();

	bool	user_exists(std::string nickname);
	bool 	user_exists(int fd);
	bool	canal_exists(std::string canal);
	bool	add_user(User *user);
	bool	add_canal(Canal *canal);

	User*	get_user(int fd);
	User*	get_user(std::string nickname);
	int		get_id(std::string nickname);
	Canal*	get_canal(std::string canal);
	int	getSocketfd() const { return socketfd; }
	int	get_port() const;
	std::string	get_password() const;

	std::map<int, User *>	get_users() const;
	
	void	broadcast(User *sender, std::string message, int skip_self = 0);

	int	handle_command(User *user, std::string buf);
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
	int	oper(User *user, std::vector<std::string> args);
	int	die(User *user, std::vector<std::string> args);
	int	topic(User *user, std::vector<std::string> args);
	int	kick(User *user, std::vector<std::string> args);
	int	pass(User *user, std::vector<std::string> args);
	int	whois(User *user, std::vector<std::string> args);
	int	notice(User *user, std::vector<std::string> args);

	std::string get_name() const;

private:
	int port;
	std::string _password;
	int socketfd;
	std::string _name;
	std::map<int, User *> users;
	std::map<std::string, int> _user_ids;
	std::map<std::string, Canal *> canals;
	struct addrinfo *socket_info;
	static std::string	_command_names[];
	static command	_commands[];

	Server();
};

#endif
