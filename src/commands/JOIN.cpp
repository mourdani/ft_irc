#include "Server.hpp"

int	Server::join(User& user, std::vector<std::string> args)
{
	std::map<std::string, Canal> canals;
	std::map<std::string, Canal>::iterator i;

	if (args.size() < 2)
		return 1;
	if (args.size() > 2)
	{
		user.send_msg("Too many arguments.\n");
		return 0;
	}
	if (args[1][0] != '#')
	{
		user.send_msg("Invalid argument. Argument must be #<canal>\n");
	}
	std::string	canal_name = args[1].substr(1, args[1].size() - 1);
	Canal	*canal = get_canal(canal_name);
	if (!canal)
	{
		Canal	new_canal(canal_name);
		canal = &new_canal;
		canal->addUser(user);
		add_canal(*canal);
		user.send_msg("Canal created.\n");
		return 0;
	}
	canal->addUser(user);
	user.send_msg("Canal joined.\n");
	return 0;
}