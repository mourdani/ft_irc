#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Server.hpp"

typedef	int (*command)(Server& server, User user, Canal channel, std::vector<std::string> args);

int handle_command(Server& server, int i, char *buf);
int	nick(Server& server, int i, std::vector<std::string> args);

#endif