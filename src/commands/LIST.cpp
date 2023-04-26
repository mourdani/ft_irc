#include  "Server.hpp"

int	Server::list(User& user, std::vector<std::string> args)
{
	(void)args;
	
	for (std::map<std::string, Canal>::iterator it = canals.begin(); it != canals.end(); ++it)
		user.send_msg(it->first + "\n");
	return 0;
}
