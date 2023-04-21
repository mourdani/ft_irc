#include "Server.hpp"
#include "commands.hpp"
#include <vector>

int	nick(Server& server, User user, Canal channel, std::vector<std::string> args)
{
	(void)server;
	(void)args;
	(void)channel;
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	user.setNickname(args[1]);
	return 0;
}

int	join(Server& server, User user, Canal channel, std::vector<std::string> args)
{
	(void)server;
	(void)args;
	(void)channel;
	(void)user;

	std::map<std::string, Canal> canals;
	std::map<std::string, Canal>::iterator i;
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	for (i = canals.begin(); i != canals.end(); i++)
	{
		if (i->second.getName().compare(args[1]) == 0)
			break ;
	}
	if (i == canals.end())
	{
		//reply to user that canal doesn't exist?
		return 0;
	}
	channel.addUser(user);
	return 0;
}


std::vector<std::string>	split(std::string str, char delimiter)
{
	size_t						start;
	size_t						end;
	std::vector<std::string>	res;

	start = 0;
	while (end != std::string::npos)
	{
		end = str.find(delimiter, start);
		res.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	return res;
}

int handle_command(Server& server, int i, char *buf)
{
	User						user_bidon("name");
	Canal						channel_bidon;
	std::vector<std::string>	sep_commands;
	std::vector<std::string>	args;
	std::string	command_names[] = {
		"NICK",
		"JOIN",
	} ;
	command	commands[] = {
		nick,
		join,
	} ;

	sep_commands = split(buf, '\n');
	for (std::vector<std::string>::iterator i = sep_commands.begin(); i != sep_commands.end(); i++)
	{
		args = split(*i, ' ');
		for (int i = 0; i < 1; i++)
		{
			if (args[0].compare(command_names[i]) == 0)
				return commands[i](server, user_bidon, channel_bidon, args);
		}
	}
	(void)server;
	(void)i;
	return 0;
}
