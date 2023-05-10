#include  "Server.hpp"

int	Server::list(User *user, std::vector<std::string> args)
{
	(void)args;
	for (std::map<std::string, Canal *>::iterator it = canals.begin(); it != canals.end(); it++)
	{
		std::stringstream ss;
		ss << it->second->getUsers().size();
		std::string n_users = ss.str();

		user->send_msg(":" + user->getServerName() + " 322 " + user->getNickname() + " " + it->second->getName() + " " + n_users + " " + it->second->getTopic());
	}
	user->send_msg(":" + user->getServerName() + " 323 " + user->getNickname() + " :End of /LIST");
	return 0;
}
