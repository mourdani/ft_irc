#include "Server.hpp"

int	Server::part(User& user, std::vector<std::string> args)
{
	std::map<std::string, Canal> canals;
	std::map<std::string, Canal>::iterator i;
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	if (args.size() > 2)
	{
		user.send_msg("Too many arguments.\n");
		return 0;
	}
	for (i = canals.begin(); i != canals.end(); i++)
	{
		if (i->second.getName().compare(args[1]) == 0)
			break ;
	}
	if (i == canals.end())
	{
		user.send_msg("This channel doesn't exist.\n");
		return 0;
	}
	i->second.removeUser(user);
	return 0;
}
