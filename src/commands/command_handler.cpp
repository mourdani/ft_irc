#include "Server.hpp"
#include "colors.hpp"
#include <vector>

std::vector<std::string>	split(std::string str, char delimiter)
{
	size_t						start;
	size_t						end;
	std::vector<std::string>	res;

	start = 0;
	while (start < str.size())
	{
		end = str.find(delimiter, start);
		if (end == std::string::npos)
			end = str.size() - 1;
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
		"PRIVMSG",
		"USER",
		"LIST",
		""
	} ;
	command	commands[] = {
		&Server::nick,
		&Server::join,
		&Server::quit,
		&Server::privmsg,
		&Server::user,
		&Server::list,
	} ;
	sep_commands = split(buf, '\n');

	for (std::vector<std::string>::iterator i = sep_commands.begin(); i != sep_commands.end(); i++)
	{
		args = split(*i, ' '); 
		if (args.size() == 0)
			continue ;
		for (int j = 0; command_names[j].size(); j++) 
		{
			if (args[0].compare(command_names[j]) == 0)
			{
				int command_ret;
				command_ret = (this->*commands[j])(user, args);
				if (i != sep_commands.end())
					continue;
				return (command_ret);
			}
		}
	}
	return 0;
}
