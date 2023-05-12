#include "Server.hpp"

int	Server::topic(User *user, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /topic <channel> [<topic>]");
		return 0;
	}
	Canal	*canal = get_canal(args[1]);
	if (!canal)
		return (user->send_code(ERR_NOSUCHCHANNEL, args[1] + " :No such channel"), 0);
	if (!canal->checkUser(user->getFd()))
		return (user->send_code(ERR_NOTONCHANNEL, args[1] + " :You're not on that channel"), 0);
	if (args.size() == 2)
	{
		if (canal->getTopic().size() == 0)
			return (user->send_code(RPL_NOTOPIC, args[1] + " :No topic is set"), 0);
		return (user->send_code(RPL_TOPIC, args[1] + " " + canal->getTopic()), 0);
	}
	if (!canal->getChanop() || *(canal->getChanop()) != *user)
	{	
		user->send_code(ERR_CHANOPRIVSNEEDED, args[1] + " :You are not chanop");
		user->send_code(RPL_TOPIC, args[1] + " " + canal->getTopic());
		return 0;
	}
	std::string	topic = "";
	for (unsigned int i = 2; i < args.size(); i++)
	{
		if (i != 2)
			topic = topic + " ";
		topic = topic + args[i];
	}
	canal->setTopic(topic);
	//std::string message;
	//message = ":" + get_name() + " ";
	//message = message + RPL_TOPIC + " " + user->getNickname();
	//message = message + " " + args[1] + topic;
	canal->broadcast(user, "TOPIC " + canal->getName() + " " + canal->getTopic());
	return 0;
}
