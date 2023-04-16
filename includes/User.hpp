//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include <string>

class User {
private:
    std::string _nickname;
    std::string _realname;
    std::string _hostname;
    bool _operator;
    User();

public:
    User(std::string hostname);

    User(const User &user);

    const std::string &getNickname() const;

    void setNickname(const std::string &nickname);

    const std::string &getRealname() const;

    void setRealname(const std::string &realname);

    const std::string &getHostname() const;

    void setHostname(const std::string &hostname);

    bool isOperator() const;

    void setOperator(bool);

    virtual ~User();

    User &operator=(const User &user);
};

std::ostream &operator<<(std::ostream &outFile, User const &user);


#endif //FT_IRC_USER_H
