#include "Server.hpp"
#include "colors.hpp"
#include <vector>
#include <algorithm>

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

int Server::handle_command(User *user, char *buf)
{

	std::vector<std::string>	sep_commands;
	std::vector<std::string>	args;

	std::string	command_names[] = {
		"JOIN", //join a channel
		"NICK", //change nickname
		"PART",	//leave a channel
		"PRIVMSG", //send a message to a user or channel
		"QUIT", //disconnect from the server
		"USER", //set username
		"LIST", //list all channels
		"PING", //ping the server
		"NAMES", //display all users in a channel
		"OPER", //set user as operator
		"TOPIC", //set topic of a channel
		"KICK", //kick a user from a channel
		"PASS", //set password
		"WHOIS", //get info about a user
		"NOTICE", //like privmsg without replying to sender
		""
	} ;
	command	commands[] = {
		&Server::join,
		&Server::nick,
		&Server::part,
		&Server::privmsg,
		&Server::quit,
		&Server::user,
		&Server::list,
		&Server::ping,
		&Server::names,
		&Server::oper,
		&Server::topic,
		&Server::kick,
		&Server::pass,
		&Server::whois,
		&Server::notice,
	} ;
	sep_commands = split(buf, '\n');

	for (std::vector<std::string>::iterator i = sep_commands.begin(); i != sep_commands.end(); i++)
	{
		args = split(*i, ' '); 
		transform(args[0].begin(), args[0].end(), args[0].begin(), ::toupper);
		if (args.size() == 0)
			continue ;
		for (int j = 0; command_names[j].size(); j++) 
		{
			if (args[0].compare(command_names[j]) == 0)
			{
				if (user->isRegistered() || args[0].compare("NICK") == 0 || args[0].compare("USER") == 0)
				{
					int command_ret;
					command_ret = (this->*commands[j])(user, args);
					if (command_ret)
						return command_ret;
				}
				else if (args[0].compare("PASS") == 0)
				{
					int command_ret;
					command_ret = (this->*commands[j])(user, args);
					if (command_ret)
						return command_ret;
				}
				else
				{
					user->send_code(ERR_NOTREGISTERED, ":You are not registered");
					return 1;
				}
			}
		}
	}
	return 0;
}
