#include "Server.hpp"

int	Server::part(User *user, std::vector<std::string> args)
{
	std::vector<std::string> canals;
	Canal	*canal;
	std::string	message = "";


	if (args.size() < 2)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /part <channel>");
		return 1;
	}
	if (args.size() >= 3)
	{
		message = " ";
		for (unsigned int i = 2; i < args.size(); i++)
		{
			message = message + args[i];
		}
	}
	canals = split(args[1], ',');
	for (std::vector<std::string>::iterator it = canals.begin(); it != canals.end(); it++)
	{
		canal = get_canal(*it);
		if (!canal)
		{
			user->send_code(ERR_NOSUCHCHANNEL, ":This channel doesn't exist.");
			continue;
		}
		if (canal->checkUser(user->getFd()) == 0)
		{
			user->send_code(ERR_NOTONCHANNEL, ":You are not on this channel.");
			continue;
		}
		canal->broadcast(user, "PART " + *it + message);
		canal->removeUser(*user);
	}
	return 0;
}
