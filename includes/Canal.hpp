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
	std::map<int, User>	_users;

public:
    Canal();
    Canal(std::string name);

    Canal(const Canal &canal);

    const std::string &getName() const;
	std::map<int, User>	getUsers() const;

    void setName(const std::string &name);

    virtual ~Canal();

    Canal &operator=(const Canal &canal);

	bool	checkUser(int id);

	void	addUser(User &user);

	void	removeUser(User user);

};

std::ostream &operator<<(std::ostream &outFile, Canal const &canal);


#endif //FT_IRC_CANAL_H
