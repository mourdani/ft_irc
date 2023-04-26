#include "Server.hpp"

int Server::user(User &user, std::vector<std::string> args)
{
	user.setUsername(args[1]);
	user.send_msg("Username set to " + args[1] + "\n");

	return 0;
}


