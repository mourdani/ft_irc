#include "Server.hpp"
#include <list>

int	Server::join(User *user, std::vector<std::string> args)
{
	std::map<std::string, Canal *> canals;
	std::vector<std::string>	channels;
	std::string					mode = "+t";

	if (args.size() < 2)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /JOIN <channel> *( \",\" <channel> )");
		return 1;
	}
	// if user is *
	if (user->getNickname() == "*" || user->getUsername() == "")
	{
		user->send_code(ERR_NOTREGISTERED, ":You didnt set your nickname/username yet");
		return 1;
	}
	channels = split(args[1], ',');
	for (std::vector<std::string>::iterator name = channels.begin(); name != channels.end(); name ++)
	{
		if ((*name)[0] != '#')
		{
			user->send_code(ERR_BADCHANMASK, *name + " :Bad Channel Mask");
			continue;
		}
		Canal	*canal = get_canal(*name);
		if (!canal)
		{
			Canal	*new_canal = new Canal(*name);
			add_canal(new_canal);
			new_canal->setChanop(user);
			canal = new_canal;
			mode = mode + "o";
		}
		if (canal->checkUser(user->getFd()))
			user->send_msg("Channel already joined.");
		else
		{
			canal->addUser(user);
			canal->broadcast(user, "JOIN " + canal->getName());
			user->send_msg(":" + user->getServerName() + " 332 " + user->getNickname() + " " + canal->getName() + " " + canal->getTopic());
			std::map<int, User *>	users = canal->getUsers();
			for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it ++)
			{
				if (canal->getChanop() && *(canal->getChanop()) == *(it->second))
					user->send_code(RPL_NAMREPLY, "= " + *name + " :@" + it->second->getNickname());
				else
					user->send_code(RPL_NAMREPLY, "= " + *name + " :" + it->second->getNickname());
			}
			user->send_msg(":" + user->getServerName() + " 366 " + user->getNickname() + " " + canal->getName() + " :End of /NAMES list.");
			// user->send_code(RPL_CHANNELMODEIS, *name + " " + mode + " " + "@m");
			// user->send_msg(user->prefix() + " MODE " + *name + " " + mode);
		}
	}
	return 0;
}
