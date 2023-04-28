//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include <string>
#include <unistd.h>

class User {
private:
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _hostname;
    bool _operator;
    int fd;

public:
    User();
    User(std::string hostname);

    User(std::string nickname, std::string realname, std::string hostname);

    User(const User &user);

    const std::string &getNickname() const;

    void setNickname(const std::string &nickname);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getRealname() const;

    void setRealname(const std::string &realname);

    const std::string &getHostname() const;

    void setHostname(const std::string &hostname);

    bool isOperator() const;

    void setOperator(bool);

    int getFd() const;

    void setFd(int fd);

    void send_msg(std::string msg);

	void	send_code(std::string code, std::string msg);

    virtual ~User();

    User &operator=(const User &user);
    bool	operator==(const User &user);
    bool	operator!=(const User &user);
};

std::ostream &operator<<(std::ostream &outFile, User const &user);


#endif //FT_IRC_USER_H
