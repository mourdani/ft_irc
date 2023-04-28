#include "Server.hpp"

int	Server::part(User *user, std::vector<std::string> args)
{
	std::map<std::string, Canal *> canals;
	std::map<std::string, Canal *>::iterator i;
	Canal	*canal;
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	canal = get_canal(args[1]);
	if (!canal)
	{
		user->send_msg("This channel doesn't exist.\n");
		return 0;
	}
	if (canal->checkUser(user->getFd()) == 0)
	{
		user->send_msg("You are not on this channel.\n");
		return 0;
	}
	canal->removeUser(*user);
	user->send_msg("Channel left.\n");
	return 0;
}
