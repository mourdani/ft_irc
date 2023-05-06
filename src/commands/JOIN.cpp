#include "Server.hpp"
#include <list>

int	Server::join(User *user, std::vector<std::string> args)
{
	std::map<std::string, Canal *> canals;
	std::vector<std::string>	channels;

	if (args.size() < 2)
		return 1;
	channels = split(args[1], ',');
	for (std::vector<std::string>::iterator name = channels.begin(); name != channels.end(); name ++)
	{
		if ((*name)[0] != '#')
		{
			user->send_code(ERR_BADCHANMASK, *name + " " + ":Bad Channel Mask");
			continue;
		}
		Canal	*canal = get_canal(*name);
		if (!canal)
		{
			Canal	*new_canal = new Canal(*name);
			add_canal(new_canal);
			new_canal->setChanop(user);
			canal = new_canal;
		}
		if (canal->checkUser(user->getFd()))
			user->send_msg("Channel already joined.\n");
		else
		{
			canal->addUser(user);
	//		std::map<int, User *>	users = canal->getUsers();

	//		std::string	message = *name;
//			//warning all users about joining
			user->send_msg(":" + user->getNickname() + " JOIN " + canal->getName() + "\r\n");
			user->send_msg(":" + user->getServerName() + " 332 " + user->getNickname() + " " + canal->getName() + " :" + canal->getTopic() + "\r\n");

			std::map<int, User *> users = canal->getUsers();
			for (std::map<int, User *>::iterator it2 = users.begin(); it2 != users.end(); it2++)
				it2->second->send_code(RPL_NAMREPLY, "= " + *name + " :@" + user->getNickname());

			user->send_code(RPL_ENDOFNAMES, *name + " :End of NAMES list");
			
			
			

			//for (std::map<int, User *>::iterator it2 = users.begin(); it2 != users.end(); it2++)
			//	it2->second->send_code(RPL_NAMREPLY, message);

			//message = *name;
			//message.append(" :").append(canal->getTopic()); //append canal description
			//user->send_code(RPL_TOPIC, message);
			//std::string	user_list;
			//message = "= ";
			//message.append(*name).append(" :@");
			//std::map<int, User *>::iterator canal_user = users.begin();
			//while (canal_user != users.end())
			//{
			//	message.append(canal_user->second->getNickname());
			//	if (++canal_user != users.end())
			//		message.append(" ");
			//}
			//user->send_code(RPL_NAMREPLY, message);
			//message = *name;
			//message.append(" :End of NAMES list");
			//user->send_code(RPL_ENDOFNAMES, message);
		}
	}
	return 0;
}
