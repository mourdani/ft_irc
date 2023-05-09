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
			user->send_msg(":" + user->getNickname() + " JOIN " + canal->getName() + "\r\n");
			user->send_msg(":" + user->getServerName() + " 332 " + user->getNickname() + " " + canal->getName() + " " + canal->getTopic() + "\r\n");
			std::map<int, User *>	users = canal->getUsers();
			for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it ++)
			{
				user->send_code(RPL_NAMREPLY, "= " + *name + " :" + it->second->getNickname());
			}
			user->send_msg(":" + user->getServerName() + " 366 " + user->getNickname() + " " + canal->getName() + " :End of /NAMES list.\r\n");
			for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it ++)
			{
				if (it->second != user)
					it->second->send_msg(":" + user->getNickname() + " JOIN " + canal->getName() + "\r\n");
			}
			//for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it ++)
			//{
			//	if (it->second != user)
			//		it->second->send_msg(":" + user->getNickname() + " JOIN " + canal->getName() + "\r\n");
			//}




		}
	}
	return 0;
}
