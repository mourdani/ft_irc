#include "Server.hpp"
#include "utils.hpp"
#include <vector>

int	Server::nick(User& user, std::vector<std::string> args)
{
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	if (get_user(args[1]) != NULL)
	{
		user.send_msg("Nickname already taken\n");
		return 0;
	}
	user.setNickname(args[1]);
	user.send_msg("Nickname successfully changed.\n");
	return 0;
}

int	Server::join(User& user, std::vector<std::string> args)
{
	std::map<std::string, Canal> canals;
	std::map<std::string, Canal>::iterator i;
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	if (args.size() > 2)
	{
		user.send_msg("Too many arguments.\n");
		return 0;
	}
	for (i = canals.begin(); i != canals.end(); i++)
	{
		if (i->second.getName().compare(args[1]) == 0)
			break ;
	}
	if (i == canals.end())
	{
		user.send_msg("This channel doesn't exist.\n");
		return 0;
	}
	i->second.addUser(user);
	return 0;
}

int	Server::part(User& user, std::vector<std::string> args)
{
	std::map<std::string, Canal> canals;
	std::map<std::string, Canal>::iterator i;
	//this shouldn't happen
	if (args.size() < 2)
		return 1;
	if (args.size() > 2)
	{
		user.send_msg("Too many arguments.\n");
		return 0;
	}
	for (i = canals.begin(); i != canals.end(); i++)
	{
		if (i->second.getName().compare(args[1]) == 0)
			break ;
	}
	if (i == canals.end())
	{
		user.send_msg("This channel doesn't exist.\n");
		return 0;
	}
	i->second.removeUser(user);
	return 0;
}

int	Server::quit(User& user, std::vector<std::string> args)
{
	(void)user;
	(void)args;
	close(user.getFd());
	return 2;
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

int Server::handle_command(User& user, char *buf)
{
	std::vector<std::string>	sep_commands;
	std::vector<std::string>	args;
	std::string	command_names[] = {
		"NICK",
		"JOIN",
		"QUIT",
	} ;
	command	commands[] = {
		&Server::nick,
		&Server::join,
		&Server::quit,
	} ;
	std::cout << "user's fd is " << user.getFd() << std::endl;
	sep_commands = split(buf, '\n');
	for (std::vector<std::string>::iterator i = sep_commands.begin(); i != sep_commands.end(); i++)
	{
		args = split(*i, ' ');
		for (int i = 0; i < 1; i++)
		{
			if (args[0].compare(command_names[i]) == 0)
				return (this->*commands[i])(user, args);
		}
	}
	return 0;
}
