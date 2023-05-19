#include "Server.hpp"

int	Server::pass(User *user, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":PASS :Not enough parameters.");
		return 1;
	}
	if (user->isRegistered())
	{
		user->send_code(ERR_ALREADYREGISTRED, ":You may not reregister");
		return 1;
	}
	if (user->getPass() == "" || user->getPass() != args[1])
		user->setPass(args[1]);
	if (get_password() == user->getPass())
	{
		user->send_code(RPL_WELCOME, ":Welcome to the Internet Relay Network.");
		user->setRegistered(true);
		return 0;
	}
	else
	{
		std::cout << "diff : " << get_password() << " " << user->getPass() << std::endl;
		user->send_code(ERR_PASSWDMISMATCH, ":Password incorrect.");
		return 1;
	}
}
