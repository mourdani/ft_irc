//
// Created by d420d4 on 10/04/23.
//

#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include <string>
#include <unistd.h>
#include <list>

class User {
private:
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _hostname;
    std::string _server_name;
    bool _operator;
    std::string _pass;
    bool _registered;
    int fd;
    std::list<std::string>	canals;
    std::string	_command;

public:
    User();
    User(std::string hostname);
    User(std::string nickname, std::string realname, std::string hostname);
    User(const User &user);
    virtual ~User();
    User &operator=(const User &user);
    bool	operator==(const User &user);
    bool	operator!=(const User &user);


    const std::string &getNickname() const;
    const std::string &getUsername() const;
    const std::string &getRealname() const;
    const std::string &getHostname() const;
    std::string	getServerName() const;
    int getFd() const;
    const std::string &getPass() const;
    bool isRegistered() const;

    void setNickname(const std::string &nickname);
    void setUsername(const std::string &username);
    void setRealname(const std::string &realname);
    void setHostname(const std::string &hostname);
    bool isOperator() const;
    void setOperator(bool);
    void setFd(int fd);
    void	setServerName(std::string name);
    void setPass(const std::string &pass);
    void setRegistered(bool registered);
	void	setCommand(std::string command);
	std::string	&getCommand();


    std::string	prefix();

    void send_msg(std::string msg);
    void send_code(std::string code, std::string msg);
    int send_unregistered_code();
};

std::ostream &operator<<(std::ostream &outFile, User const &user);


#endif //FT_IRC_USER_H
