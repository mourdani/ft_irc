#include "Server.hpp"

int	Server::nick(User *user, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		user->send_code(ERR_NONICKNAMEGIVEN, ":No nickname given");
		return 0;
	}
	if (!user->isRegistered() && user->getNickname().compare("*"))
		return 0;
	if (get_user(args[1]) != NULL)
	{
		user->send_code(ERR_NICKNAMEINUSE, args[1] + " :Nickname is already in use.");
		if (user->getNickname().compare("*") == 0)
		{
			quit(user, args);
			return BAD_USER;
		}
		return 0;
	}
	_user_ids.erase(user->getNickname());
	std::pair<std::string, int>	pair;
	pair.first = args[1];
	pair.second = user->getFd();
	_user_ids.insert(std::pair<std::string, int>(args[1], user->getFd()));
	broadcast(user, "NICK " + args[1]);
	user->setNickname(args[1]);
	return 0;
}
