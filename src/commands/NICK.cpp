#include "Server.hpp"

int	Server::nick(User& user, std::vector<std::string> args)
{
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	if (get_user(args[1]) != NULL)
	{
		user.send_code("443", args[1].append(" :Nickname is already in use.\n"));
		return 1;
	}
	_user_ids.erase(user.getNickname());
	std::pair<std::string, int>	pair;
	pair.first = args[1];
	pair.second = user.getFd();
	_user_ids.insert(std::pair<std::string, int>(args[1], user.getFd()));
	user.setNickname(args[1]);
	user.send_msg("Nickname successfully changed.\n");
	return 0;
}