#include "Server.hpp"
#include <algorithm>

Server::~Server() {
	close(socketfd);
	std::map<int, User *>::iterator	user;
	for (user = users.begin(); user != users.end(); user++)
		delete user->second;
	std::map<std::string, Canal *>::iterator	canal;
	for (canal = canals.begin(); canal != canals.end(); canal++)
		delete canal->second;	
}

int Server::init() {
    struct addrinfo *result;
    
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints)); // Initialize hints struct to zero
// 
    hints.ai_family = AF_INET;       /* Allow IPv6 */
    hints.ai_socktype = SOCK_STREAM;  /* Stream socket */
    hints.ai_flags = AI_PASSIVE;      /* For wildcard IP address */

    std::stringstream ss;
    ss << port;
    std::string port_str = ss.str();
    const char *port_char = port_str.c_str();

    if (getaddrinfo(NULL, port_char, &hints, &result) != 0) {
        std::cerr << "Failed to get address information." << std::endl;
        throw std::exception();
    }
    
    try {
        while (result != NULL) {
            this->socketfd = socket(result->ai_family,
                              result->ai_socktype,
                              result->ai_protocol);

            if (this->socketfd == -1) {
                result = result->ai_next; // Try next address
                continue;
            }

            if (bind(this->socketfd, result->ai_addr, result->ai_addrlen) == 0) {
                std::cout << "Server listening on port " \
                    << GREEN << port << RESET << std::endl;
                break;
            }

            close(this->socketfd); // Close socket if bind fails
            result = result->ai_next; // Try next address
        }

        if (result == NULL) {
            std::cerr << "Could not bind" << std::endl;
            throw std::exception();
        }

        if (listen(this->socketfd, MAX_CLIENTS) < 0) {
            std::cerr << "Failed to listen" << std::endl;
            throw std::exception();
        }
    } catch (std::exception &e) {
        std::cerr << "Failed to initialize server" << std::endl;
		return 1;
    }
	return 0;
}

void Server::run() {
    struct pollfd fds[MAX_CLIENTS];
    int nfds = 1;
    int timeout = 1000;


	Canal *general = new Canal("#general");
	add_canal(general);
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
                char buf[1024];
                memset(buf, 0, 1024);
                int len = recv(fds[i].fd, buf, 1024, MSG_DONTWAIT);
                if (len == 0) {
                    std::cout << "Client " << i << " disconnected" << std::endl;
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    continue;
				}
				User	*user = this->get_user(fds[i].fd);

				std::cout << "Client " << i << " sent: " << buf;
				if (user == NULL)
					std::cout << "Something is very wrong\n";
				else
				{
					if (handle_command(user, buf) == 2)
						fds[i].fd = -1;
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


Canal *Server::get_canal(std::string canal) {
	std::map<std::string, Canal *>::iterator it = canals.find(canal);
	if (it == canals.end())
		return NULL;
    return it->second;
}

std::string Server::get_name() const {
    return this->_name;
}
