#include "Server.hpp"

int	Server::ping(User *user, std::vector<std::string> args)
{
	(void)user;
	(void)args;

	user->send_msg("PONG " + get_name());
	return 0;
}
