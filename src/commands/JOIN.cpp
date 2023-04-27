#include "Server.hpp"
#include <list>

int	Server::join(User& user, std::vector<std::string> args)
{
	std::map<std::string, Canal> canals;
	std::map<std::string, Canal>::iterator i;
	std::vector<std::string>	channels;

	if (args.size() < 2)
		return 1;
	channels = split(args[1], ',');
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it ++)
	{
		Canal	*canal = get_canal(*it);
		(void)user;
		if (!canal)
		{
			Canal	new_canal(*it);
			add_canal(new_canal);
			canal = &new_canal;
		}
		if (canal->checkUser(user.getFd()))
			user.send_msg("Channel already joined.\n");
		else
		{
			canal->addUser(user);
			std::map<int, User>	users = canal->getUsers();

			//warning all users about joining
			std::string	message(user.getNickname());
			message.append("!").append(user.getHostname()).append(" JOIN ").append(*it).append("\n");
			for (std::map<int, User>::iterator it2 = users.begin(); it2 != users.end(); it2++)
				it2->second.send_msg(message);

			message = *it;
			message.append(" :").append("temporary description"); //append canal description
			user.send_code("332", message);
			std::string	user_list;
			message = "= ";
			message.append(*it).append(" :@");
			std::map<int, User>::iterator canal_user = users.begin();
			while (canal_user != users.end())
			{
				if (!get_user(*it))
				{
					canal_user++;
					continue ;
				}
				message.append(get_user(*it)->getNickname());
				if (++canal_user != users.end())
					message.append(" ");
			}
			user.send_code("353", message);
			message = *it;
			message.append(" :End of NAMES list");
			user.send_code("366", message);
		}
	}
	return 0;
}