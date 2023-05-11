#include "Server.hpp"

#include "Server.hpp"

int	notice_canal(Server *server, User *user, std::string dest, std::string message)
{
	Canal	*canal;
	canal = server->get_canal(dest);
	if (canal)
	{
		if (!canal->checkUser(user->getFd()))
			return 0;
		std::map<int, User *>	users = canal->getUsers();
		std::map<int, User *>::iterator	it;
		for (it = users.begin(); it != users.end(); it++)
		{
			if (it->second != user)
				it->second->send_msg(message);
		}
		return 0;
	}
	return 1;
}

int	Server::notice(User *user, std::vector<std::string> args)
{
	if (args.size() < 3)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /NOTICE <dest> <msg>");
		return 0;
	}
	std::vector<std::string>	destinations = split(args[1], ',');
	std::string	message;
	std::string	sender;

	sender = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " NOTICE" + " ";
	message = "";
	for (unsigned int i = 2; i < args.size(); i ++)
	{
		message.append(" ");
		message.append(args[i]);
	}
	for (std::vector<std::string>::iterator dest = destinations.begin(); dest != destinations.end(); dest++)
	{
		if ((*dest)[0] == '#')
		{
			if (notice_canal(this, user, *dest, sender + *dest + message) == 0)
				continue;
		}
		User	*dest_user = get_user(*dest);
		if (dest_user)
			dest_user->send_msg(sender + *dest + message);
	}
	return 0;
}