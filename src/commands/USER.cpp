#include "Server.hpp"

int Server::user(User *user, std::vector<std::string> args)
{
	if (user->getUsername().compare(""))
		return 0;
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (it->second->getUsername().compare(args[1]) == 0)
		{
			user->send_code(ERR_ALREADYREGISTRED, args[1] + " :Unauthorized command (already registered)");
			quit(user, args);
			return BAD_USER;
		}
	}
	user->setUsername(args[1]);
	return 0;
}


