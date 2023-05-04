#include "Server.hpp"

int	Server::whois(User *user, std::vector<std::string> args)
{
	if (args.size() < 2)
		return 1;
	User *target = get_user(args[1]);
	if (target == NULL)
	{
		user->send_code(ERR_NOSUCHNICK, "No such nickname\r\n" + args[1]);
		return 0;
	}
	user->send_code(RPL_WHOISUSER, target->getNickname() + " " + target->getUsername() + " " + target->getHostname() + " * :" + target->getRealname());

	return 0;
}
