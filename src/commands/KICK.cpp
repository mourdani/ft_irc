#include "Server.hpp"

int	Server::kick(User *user, std::vector<std::string> args)
{
	Canal	*canal;

	if (args.size() < 3)
		return (user->send_code(ERR_NEEDMOREPARAMS, ":Usage: KICK <channel> <user> *( \",\" <user> )"), 0);
	if (args[1][0] != '#')
		return (user->send_code(ERR_BADCHANMASK, ":Bad channel mask"), 0);
	canal = get_canal(args[1]);
	if (!canal)
		return (user->send_code(ERR_NOSUCHCHANNEL, args[1] + " :No such channel"), 0);
	if (canal->checkUser(user->getFd()) == 0)
		return (user->send_code(ERR_NOTONCHANNEL, args[1] + " :You are not on this channel"), 0);
	if (!canal->getChanop() || *(canal->getChanop()) != *user)
		return (user->send_code(ERR_CHANOPRIVSNEEDED, args[1] + " :You are not chanop"), 0);

	std::vector<std::string>	to_kick = split(args[2], ',');
	std::string	message = "";
	for (unsigned int i = 3; i < args.size(); i ++)
	{
		message.append(" ");
		message.append(args[i]);
	}
	for (std::vector<std::string>::iterator it = to_kick.begin(); it != to_kick.end(); it++)
	{
		int	user_id = get_id(*it);
		if (user_id < 0 || canal->checkUser(user_id) == 0)
		{
			user->send_code(ERR_USERNOTINCHANNEL, *it + " " + args[1] + " :They aren't on that channel");
			continue;
		}
		canal->broadcast(user, "KICK " + args[1] + " " + *it + message);
		canal->removeUser(user_id);
	}
	return 0;
}
