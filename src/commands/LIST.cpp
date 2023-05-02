#include  "Server.hpp"

int	Server::list(User *user, std::vector<std::string> args)
{
	(void)args;
	
	std::map<std::string, Canal *>::iterator it = canals.begin();

	while (it != canals.end())
	{
		std::stringstream ss;
		ss << it->second->getUsers().size();
		std::string size = ss.str();
		user->send_code(RPL_LIST, it->second->getName() + " " + size + ":" + it->second->getTopic());
		it++;
	}
	user->send_code(RPL_LISTEND, "==================");
	return 0;
}
