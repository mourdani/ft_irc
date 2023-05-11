#include "Server.hpp"

int	Server::oper(User *user, std::vector<std::string> args)
{
	if (args.size() < 3)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /OPER <name> <password>");
		return 0;
	}
	if (args[1].compare("name") || args[2].compare("password"))
	{
		user->send_code(ERR_PASSWDMISMATCH, ":Wrong name or password");
		return 0;
	}
	user->setOperator(true);
	user->send_code(RPL_YOUREOPER, ":You are now an IRC operator");
	// user->send_msg(user->prefix() + " MODE " + user->getNickname() + " +o");
	return 0;
}
