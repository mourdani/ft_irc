#include "Server.hpp"

int	Server::privmsg(User *user, std::vector<std::string> args)
{
	if (args.size() < 3)
	{
		user->send_msg("Not enough arguments.");
		return 0;
	}
	std::string	message;
	message = args[0];
	message.append(" ");
	message.append(user->getNickname());
	if (args[1][0] == '#')
	{
		message.append(" ");
		message.append(args[1]);
	}
	for (unsigned int i = 2; i < args.size(); i ++)
	{
		message.append(" ");
		message.append(args[i]);
	}
	message.append("\n");
	if (args[1][0] == '#')
	{
		Canal	*canal;
		canal = get_canal(args[1]);
		if (canal)
		{
			if (!canal->checkUser(user->getFd()))
			{
				user->send_code("404", ":Cannot send to channel");
				user->send_msg("You are not a member of this channel. Use /join.\n");
				return 0;
			}
			std::map<int, User *>	users = canal->getUsers();
			std::map<int, User *>::iterator	it;
			for (it = users.begin(); it != users.end(); it++)
			{
				if (it->second != user)
					it->second->send_msg(message);
			}
			return 0;
		}
	}
	User	*dest = get_user(args[1]);
	if (dest)
	{
		dest->send_msg(message);
		return 0;
	}
	user->send_code("401", ": No such nick/channel");
	return 0;
}