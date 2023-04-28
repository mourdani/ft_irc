#include "Server.hpp"

int	Server::names(User& user, std::vector<std::string> args) // missing channel arg to show users in channel
{
	(void)args;
	std::string names;
	std::map<int, User>::iterator it = users.begin();
	while (it != users.end())
	{
		names += it->second.getNickname() + " ";
		it++;
	}
	user.send_msg(":" + get_name() + " 353 " + " = " + get_name() + " :" + names + "\r\n");
	user.send_msg(":" + get_name() + " 366 " + " " + user.getNickname() + " :End of /NAMES list.\r\n");
	return 0;
}
