//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_CANAL_H
#define FT_IRC_CANAL_H

#include <string>
#include <map>
#include "User.hpp"

class Canal {
private:
	std::string _name;
	std::string _topic;
	std::map<int, User *>	_users;
	User	*_chanop;

public:
    Canal();
    Canal(std::string name);

    Canal(const Canal &canal);

    const std::string &getName() const;
	std::map<int, User *>	getUsers() const;

    void setName(const std::string &name);

    virtual ~Canal();

    Canal &operator=(const Canal &canal);

	void	setChanop(User *user);

	User	*getChanop();

	bool	checkUser(int id);

	void	addUser(User *user);

	void	removeUser(User user);

	void	removeUser(int id);

	void	broadcast(User *sender, std::string message, int skip_self = 0);


    void   setTopic(const std::string &topic);
    std::string getTopic() const;
};

std::ostream &operator<<(std::ostream &outFile, Canal const &canal);


#endif //FT_IRC_CANAL_H
