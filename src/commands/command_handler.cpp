#include "Server.hpp"
#include "commands.hpp"
#include <vector>

int	nick(Server& server, int i, std::vector<std::string> args)
{
	(void)server;
	(void)i;
	(void)args;
	for (std::vector<std::string>::iterator i = args.begin(); i != args.end(); i ++)
	{
		std::cout << "argument : " << *i << std::endl;
	}
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
	std::vector<std::string>	sep_commands;
	std::vector<std::string>	args;
	std::string	command_names[] = {
		"NICK",
	} ;
	command	commands[] = {
		nick,
	} ;

	sep_commands = split(buf, '\n');
	for (std::vector<std::string>::iterator i = sep_commands.begin(); i != sep_commands.end(); i++)
	{
		args = split(*i, ' ');
		for (int i = 0; i < 1; i++)
		{
			if (args[0].compare(command_names[i]) == 0)
				return commands[i](server, i, args);
		}
	}
	(void)server;
	(void)i;
	return 0;
}
