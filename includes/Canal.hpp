//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_CANAL_H
#define FT_IRC_CANAL_H

#include <string>
#include <vector>
#include "User.hpp"

class Canal {
private:
    std::string _name;
    std::vector<std::string> _users; //hostname of user


public:
    Canal();
    Canal(std::string name);

    Canal(const Canal &canal);

    const std::string &getName() const;

    void setName(const std::string &name);

    virtual ~Canal();

    Canal &operator=(const Canal &canal);
};

std::ostream &operator<<(std::ostream &outFile, Canal const &canal);


#endif //FT_IRC_CANAL_H
