#include "Server.hpp"

int	Server::kill(User *user, std::vector<std::string> args)
{
	(void)args;
	if (user->isOperator() == false)
	{
		user->send_code(ERR_NOPRIVILEGES, "You are not an operator.");
		return 0;
	}
	return KILL;
}
