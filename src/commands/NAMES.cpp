#include "Server.hpp"

int	Server::names(User *user, std::vector<std::string> args){
	std::string names;
	std::map<int, User *>::iterator it = users.begin();

	if (args.size() < 2)
	{
		user->send_code(ERR_NEEDMOREPARAMS, "/NAMES <channel>");
		return 0;
	}
	if (args[1].find_first_not_of("0123456789") == std::string::npos) 
	{
		while (it != users.end())
		{
			names += it->second->getNickname() + " ";
			it++;
		}
		user->send_code(RPL_NAMREPLY, "= " + get_name() + " : " + names);
		user->send_code(RPL_ENDOFNAMES, "");
		return 0;
	}
	Canal *canal = get_canal(args[1]);
	if (!canal)
		return (user->send_code(ERR_NOSUCHCHANNEL, args[1] + " :No such channel"), 0);

	std::map<int, User *> users = canal->getUsers();
	std::map<int, User *>::iterator it2 = users.begin();
	while (it2 != users.end())
	{
		if (*(it2->second) == *(canal->getChanop()))
			names+= "@";
		names += it2->second->getNickname() + " ";
		it2++;
	}
	user->send_code(RPL_NAMREPLY, "= " + canal->getName() + " : " + names);
	user->send_code(RPL_ENDOFNAMES, "");
	return 0;
} 
