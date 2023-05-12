#include "Server.hpp"
#include <algorithm>

Server::Server(int port, std::string password) : port(port), _password(password), _name("42_FT_IRC") {
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    std::stringstream ss;
    ss << this->port;
    std::string port_str = ss.str();

    int status = getaddrinfo(NULL, port_str.c_str(), &hints, &socket_info);
    if (status != 0) {
        std::cerr << "getaddrinfo error!" << std::endl;
        //return 1;
        exit(1);
    }

    struct addrinfo *p;
    for (p = socket_info; p != NULL; p = p->ai_next) {
        this->socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->socketfd == -1) {
            continue;
        }

        int yes = 1;
        if (setsockopt(this->socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
            std::cerr << "setsockopt error!" << std::endl;
            //return 1;
            exit(1);
        }

        if (bind(this->socketfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(this->socketfd);
            continue;
        }

        break;
    }
    freeaddrinfo(socket_info);

    if (p == NULL) {
        std::cerr << RED << "Could not bind to port [" << get_port() << "] address already in use" << std::endl;
        std::cerr << "Use another port or wait for the port to close correctly." << std::endl;
        std::cerr << "To check port state:  netstat -an | grep " << get_port() << RESET << std::endl;
        freeaddrinfo(socket_info);
        //return 1;
        exit(1);
    }

    if (listen(this->socketfd, MAX_CLIENTS) == -1) {
        std::cerr << "listen error!" << std::endl;
        //return 1;
        exit(1);
    }

    std::cout << "Server listening on port " << GREEN << port << RESET << std::endl;
}


Server::~Server() {
    std::map<int, User *>::iterator it = users.begin();
    while (it != users.end()) {
        close(it->first); 
        it++;
    }
    close(socketfd);
    std::map<int, User *>::iterator	user;
    for (user = users.begin(); user != users.end(); user++)
    	delete user->second;
    std::map<std::string, Canal *>::iterator	canal;
    for (canal = canals.begin(); canal != canals.end(); canal++)
        delete canal->second;
}

int Server::run() {
    struct pollfd fds[MAX_CLIENTS];
    memset(fds, 0, sizeof(fds));
    int nfds = 1;
    int timeout = 1000;


   // Canal *general = new Canal("#general");
   // add_canal(general);
    fds[0].fd = this->socketfd;
    fds[0].events = POLLIN;
    while (1) {
        int ret = poll(fds, nfds, timeout);
        if (ret == -1) {
            std::cerr << "Poll failed" << std::endl;
            break;
        }
        if (fds[0].revents & POLLIN) { // New connection
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);

            int client_fd = accept(this->socketfd, (struct sockaddr*)&client_addr, &client_len);

            if (client_fd < 0) {
                std::cerr << "Accept failed" << std::endl;
                continue;
            }

            fds[nfds].fd = client_fd;
            fds[nfds].events = POLLIN;
            nfds++;

            User	*user = new User(inet_ntoa(client_addr.sin_addr));
            user->setFd(client_fd);
            this->add_user(user);
        }
        
        for (int i = 1; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                User	*user = this->get_user(fds[i].fd);
                char buf[1024];
                memset(buf, 0, 1024);
                int len = recv(fds[i].fd, buf, 1024, MSG_DONTWAIT);
                if (len == 0) {
                    std::cout << "Client " << i << " disconnected" << std::endl;
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    continue;
                }
			
				std::cout << BOLDMAGENTA << "Received from " << user->getNickname() << ": " << buf << RESET << std::endl;
				if (user == NULL)
					std::cout << "Something is very wrong";
				else
				{
					int	ret = handle_command(user, buf);
					if (ret == QUIT || ret == BAD_USER)
						fds[i].fd = -1;
					if (ret == DIE)
						return DIE;
				}
				memset(buf, 0, 1024);
            }
        }

        for (int i = 1; i < nfds; i++) {
            if (fds[i].fd == -1) {
                for (int j = i; j < nfds - 1; j++) {
                    fds[j].fd = fds[j + 1].fd;
                }
                i--;
                nfds--;
            }
        }
    }
	return 0;
}

bool Server::user_exists(int fd) {
	std::map<int, User *>::iterator it;
	it = this->users.find(fd);
	if (it == this->users.end())
		return 0;
    return 1;
}

bool Server::user_exists(std::string nickname) {
    for (std::map<int, User *>::iterator it = this->users.begin(); it != this->users.end(); ++it)
        if (it->second->getNickname() == nickname)
            return true;

    return false;
}

bool Server::canal_exists(std::string canal) {
    for (std::map<std::string, Canal *>::iterator it = this->canals.begin(); it != this->canals.end(); ++it)
        if (it->second->getName() == canal)
            return true;

    return false;
}

bool Server::add_user(User *user) {
	if (user_exists(user->getFd()))
		return false;
	user->setServerName(_name);
	this->users.insert(std::pair<int, User *>(user->getFd(), user));
	this->_user_ids.insert(std::pair<std::string, int>(user->getNickname(), user->getFd()));
	return true;
}

bool Server::add_canal(Canal *canal) {
    if (canal_exists(canal->getName()))
        return false;
    this->canals.insert(std::pair<std::string, Canal *>(canal->getName(), canal));

    return true;
}

User *Server::get_user(int fd) {
	std::map<int, User *>::iterator it;
	it = this->users.find(fd);
	if (it == this->users.end())
		return NULL;
    return it->second;
}

User*	Server::get_user(std::string nickname)
{
	std::map<std::string, int>::iterator it;
	it = _user_ids.find(nickname);
	if (it == _user_ids.end())
		return NULL;
	return (get_user(it->second));
}

int		Server::get_id(std::string nickname)
{
	std::map<std::string, int>::iterator it;
	it = _user_ids.find(nickname);
	if (it == _user_ids.end())
		return -1;
	return it->second;
}


Canal *Server::get_canal(std::string canal) {
	std::map<std::string, Canal *>::iterator it = canals.find(canal);
	if (it == canals.end())
		return NULL;
    return it->second;
}

std::string Server::get_name() const {
    return this->_name;
}

std::map<int, User *> Server::get_users() const {
    return this->users;
}

int Server::get_port() const {
    return this->port;
}

std::string Server::get_password() const {
    return this->_password;
}
