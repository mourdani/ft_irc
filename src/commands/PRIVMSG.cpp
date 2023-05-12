#include "Server.hpp"

int	message_canal(Server *server, User *user, std::string dest, std::string message)
{
	Canal	*canal;
	canal = server->get_canal(dest);
	if (canal)
	{
		if (!canal->checkUser(user->getFd()))
		{
			user->send_code(ERR_CANNOTSENDTOCHAN, dest + " :Cannot send to channel");
			return 0;
		}
		std::map<int, User *>	users = canal->getUsers();
		std::map<int, User *>::iterator	it;
		canal->broadcast(user, "PRIVMSG " + dest + message, 1);
		return 0;
	}
	return 1;
}

int	Server::privmsg(User *user, std::vector<std::string> args)
{
	if (args.size() < 3)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /msg <dest> <msg>");
		return 0;
	}
	std::vector<std::string>	destinations = split(args[1], ',');
	std::string	message;

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
			if (message_canal(this, user, *dest, message) == 0)
				continue;
		}
		User	*dest_user = get_user(*dest);
		if (dest_user && dest_user->isRegistered())
			dest_user->send_msg(user->prefix() + " PRIVMSG " + *dest + message);
		else
			user->send_code(ERR_NOSUCHNICK, *dest + " :No such nick/channel");
	}
	return 0;
}
