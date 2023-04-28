#include  "Server.hpp"

int	Server::list(User *user, std::vector<std::string> args)
{
	(void)args;
	
	std::map<std::string, Canal *>::iterator it = canals.begin();
	std::string msg; 

	while (it != canals.end())
	{
		std::stringstream ss;
		ss << it->second->getUsers().size();
		std::string size = ss.str();
		msg = ":" + get_name() + " 322 " + user->getNickname() + " " + it->second->getName() + " " + size + " :" + it->second->getTopic() + "\r\n";
		user->send_msg(msg);
		it++;
	}
	user->send_msg(":" + get_name() + " 323 " + user->getNickname() + " ==================\r\n");
	return 0;
}
