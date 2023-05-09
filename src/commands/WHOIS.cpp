#include "Server.hpp"

int Server::whois(User *user, std::vector<std::string> args) {
	if (args.size() < 2) {
		user->send_msg(":" + user->getNickname() + " 461 " + user->getNickname() + " WHOIS :Not enough parameters\r\n");
		return 0;
	}

	if (user_exists(args[1]) == false) {
		user->send_msg(":" + user->getNickname() + " 401 " + user->getNickname() + " " + args[1] + " :No such nick\r\n");
		return 0;
	}
	User *target = get_user(args[1]);
	user->send_msg(":" + user->getNickname() + " 311 " + user->getNickname() + " " + target->getNickname() + " " + target->getUsername() + " " + target->getHostname() + " * :" + target->getRealname() + "\r\n");
	user->send_msg(":" + user->getNickname() + " 312 " + user->getNickname() + " " + target->getNickname() + " " + target->getServerName() + "\r\n");
	user->send_msg(":" + user->getNickname() + " 318 " + user->getNickname() + " " + target->getNickname() + " :End of WHOIS list\r\n");
	return 0;
}
