#include "Server.hpp"
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
			end = str.size();
		res.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); it++)
	{
		start = it->find('\r');
		while (start != std::string::npos)
		{
			it->erase(start);
			start = it->find('\r');
		}
	}
	return res;
}

std::string	Server::command_reply(int code, std::string reply) const
{
	std::stringstream	stream;
	std::string			str;
	stream << code;
	str = stream.str();
	while (str.size() < 3)
		str.insert(0, "0");
	str.append(" ");
	str.append(reply);
	return (str);
}


int Server::handle_command(User& user, char *buf)
{
	std::vector<std::string>	sep_commands;
	std::vector<std::string>	args;
	std::string	command_names[] = {
		"JOIN",
		"NICK",
		"PART",
		"PRIVMSG",
		"QUIT",
		""
	} ;
	command	commands[] = {
		&Server::join,
		&Server::nick,
		&Server::part,
		&Server::privmsg,
		&Server::quit,
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
				return (this->*commands[j])(user, args);
		}
	}
	return 0;
}
