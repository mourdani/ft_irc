<p align="center">
    <h1 align="center">FT_IRC</h1>
</p>
<p align="center">
    <em>Empower communication with FT_IRC: Your Gateway to Connectivity.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/mourdani/ft_irc?style=flat&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/mourdani/ft_irc?style=flat&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/mourdani/ft_irc?style=flat&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/mourdani/ft_irc?style=flat&color=0080ff" alt="repo-language-count">
<p>
<p align="center">
		<em>Developed with the software and tools below.</em>
</p>
<p align="center">
	</p>
<hr>

## 🔗 Quick Links

> - [📍 Overview](#-overview)
> - [📂 Repository Structure](#-repository-structure)
> - [🧩 Modules](#-modules)
> - [🚀 Getting Started](#-getting-started)


---
## 📍 Overview

The ft_irc project is an IRC server-client communication system that facilitates essential functionalities such as JOIN, PART, and PRIVMSG. It utilizes classes like Canal.hpp and User.hpp to manage communication channels, user details, and network interactions efficiently. The Server.hpp file plays a crucial role in handling connections, socket operations, and message parsing, ensuring seamless data exchange between clients. Moreover, errorCodes.hpp defines error codes for server responses, improving communication integrity. With features like color constants in colors.hpp for enhanced readability, ft_irc offers a robust solution for effective IRC communication.

---
---

## 📂 Repository Structure

```sh
└── ft_irc/
    ├── Makefile
    ├── includes
    │   ├── Canal.hpp
    │   ├── Server.hpp
    │   ├── User.hpp
    │   ├── colors.hpp
    │   └── errorCodes.hpp
    └── src
        ├── Canal.cpp
        ├── Server.cpp
        ├── User.cpp
        ├── commands
        │   ├── DIE.cpp
        │   ├── JOIN.cpp
        │   ├── KICK.cpp
        │   ├── LIST.cpp
        │   ├── NAMES.cpp
        │   ├── NICK.cpp
        │   ├── NOTICE.cpp
        │   ├── OPER.cpp
        │   ├── PART.cpp
        │   ├── PASS.cpp
        │   ├── PING.cpp
        │   ├── PRIVMSG.cpp
        │   ├── QUIT.cpp
        │   ├── TOPIC.cpp
        │   ├── USER.cpp
        │   ├── WHOIS.cpp
        │   └── command_handler.cpp
        └── main.cpp
```

---

## 🧩 Modules

<details closed><summary>.</summary>

| File                                                                | Summary                                                                                                                                                                          |
| ---                                                                 | ---                                                                                                                                                                              |
| [Makefile](https://github.com/mourdani/ft_irc/blob/master/Makefile) | Code snippet manages IRC commands in the ft_irc repository, supporting functionality like JOIN, PART, and PRIVMSG. Critical for server-client communication in the architecture. |

</details>

<details closed><summary>includes</summary>

| File                                                                                     | Summary                                                                                                                                                                                                                                          |
| ---                                                                                      | ---                                                                                                                                                                                                                                              |
| [errorCodes.hpp](https://github.com/mourdani/ft_irc/blob/master/includes/errorCodes.hpp) | Code snippet in `includes/errorCodes.hpp` defines error codes for IRC server responses, with `RPL_TOPIC` for topic retrieval. Maintains server-client communication integrity within the repository architecture.                                |
| [Canal.hpp](https://github.com/mourdani/ft_irc/blob/master/includes/Canal.hpp)           | Code snippet in Canal.hpp defines a class for handling communication channels. Manages channel properties and users. Integral part of FT_IRC architecture.                                                                                       |
| [Server.hpp](https://github.com/mourdani/ft_irc/blob/master/includes/Server.hpp)         | Code snippet summary: Server class manages network communication, encapsulating socket handling and message parsing for the IRC server. Essential component of the IRC server architecture, handling connections and data exchange with clients. |
| [User.hpp](https://github.com/mourdani/ft_irc/blob/master/includes/User.hpp)             | This User class manages user details like nickname with relevant methods for parent repository's IRC server architecture.                                                                                                                        |
| [colors.hpp](https://github.com/mourdani/ft_irc/blob/master/includes/colors.hpp)         | Code snippet in `colors.hpp` enhances ft_irc's readability with color constants, vital for error indication and user interface enhancement in the server-client communication feature.                                                           |

</details>

<details closed><summary>src</summary>

| File                                                                        | Summary                                                                                                                                                                                                                                              |
| ---                                                                         | ---                                                                                                                                                                                                                                                  |
| [User.cpp](https://github.com/mourdani/ft_irc/blob/master/src/User.cpp)     | Code Summary: `src/User.cpp`**Manages user functionality in `ft_irc`, integrating with the server. Interaction handling and state management pivotal in IRC protocol implementation.                                                                 |
| [Canal.cpp](https://github.com/mourdani/ft_irc/blob/master/src/Canal.cpp)   | `src/Canal.cpp` in `ft_irc` repo manages communication channels. Implements channel functionality like joining, leaving, and sending messages. Vital for server-client messaging system.                                                     |
| [main.cpp](https://github.com/mourdani/ft_irc/blob/master/src/main.cpp)     | Code Summary:**Maintains server instance & handles startup. Relies on Server class for IRC server functionality. Critical for initializing server operations & coordinating client interactions. Facilitates reliable & efficient server management. |
| [Server.cpp](https://github.com/mourdani/ft_irc/blob/master/src/Server.cpp) | Code Summary:** `Server.cpp` manages server functionality, utilizing `Server.hpp`. Key features involve server operations coordination within the `ft_irc` architecture.                                                                             |

</details>

<details closed><summary>src.commands</summary>

| File                                                                                                   | Summary                                                                                                                                                                                                                                                                    |
| ---                                                                                                    | ---                                                                                                                                                                                                                                                                        |
| [TOPIC.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/TOPIC.cpp)                     | Code snippet in `ft_irc/src/commands/PRIVMSG.cpp` manages sending private messages within the IRC server, facilitating real-time communication among users. It bolsters user interaction and enhances the server's messaging system.                                       |
| [PASS.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/PASS.cpp)                       | Code snippet: `PASS.cpp`Summary: `Enables user authentication, requiring minimum 2 arguments. Integrates auth method within server, ensuring secure access for users.`                                                                                                     |
| [PRIVMSG.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/PRIVMSG.cpp)                 | Code snippet `PRIVMSG.cpp` in `ft_irc` repo handles messaging logic using `Server` features. It includes `Server.hpp` and defines `int message`, playing a key role in facilitating communication in the system.                                                           |
| [KICK.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/KICK.cpp)                       | Code snippet summary: Implements JOIN command feature in IRC server. Responsible for handling user joining a channel functionality. Part of comprehensive commands module in ft_irc repository architecture.                                                               |
| [JOIN.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/JOIN.cpp)                       | ft_irc/src/commands/JOIN.cpp`Summary: Parses and processes user JOIN commands, adding users to the specified channel in the IRC server architecture.                                                                                                                       |
| [WHOIS.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/WHOIS.cpp)                     | Code snippet in `WHOIS.cpp` ➡️ `Server::whois` method for fetching user info. Utilizes `User` class. Serves WHOIS command functionality in the IRC server system architecture.                                                                                             |
| [command_handler.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/command_handler.cpp) | Code snippet summary:In `src/`, `command_handler.cpp` in the `ft_irc` repo orchestrates and routes IRC commands, enabling server-side processing for user interactions.                                                                                                    |
| [OPER.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/OPER.cpp)                       | Code Summary:**`OPER.cpp` in `ft_irc` repo validates operator login for IRC users. Ensures correct name and password input, sets operator status, and sends appropriate confirmation.                                                                                      |
| [PART.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/PART.cpp)                       | Code Summary:** `PART.cpp` in `ft_irc` repo handles user leaving a channel. Core feature: managing user's departure from the channel. Relies on `Server.hpp`.For a more comprehensive understanding, refer to the code snippet from `PART.cpp` in the `ft_irc` repository. |
| [USER.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/USER.cpp)                       | ROLE:** `USER.cpp` in `ft_irc` handles user registration within the IRC server. Validates user data and updates username. Supports error messaging and parameter checks.                                                                                                   |
| [LIST.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/LIST.cpp)                       | Code snippet in LIST.cpp lists users in a channel. Includes Server.hpp. Implements list() method to display users. Essential for command handling in ft_irc repo architecture.                                                                                             |
| [NOTICE.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/NOTICE.cpp)                   | NOTICE.cpp in ft_irc/src/commands notifies users via Server interactions, embedded within a broader network communication system in the parent repository.                                                                                                                 |
| [QUIT.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/QUIT.cpp)                       | Code Summary:**`QUIT.cpp` in `ft_irc` repository's `commands` handles user quitting. Cleans up user data and broadcasts status before removing from channels.                                                                                                              |
| [DIE.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/DIE.cpp)                         | Code Summary:**`src/commands/DIE.cpp` in `ft_irc` checks user privileges before allowing server shutdown. Helps maintain security by restricting operator access.                                                                                                          |
| [PING.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/PING.cpp)                       | PING command in ft_irc**Handles PING command in the IRC server.References Server.hpp for implementation.Responds with a PONG message.                                                                                                                                      |
| [NAMES.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/NAMES.cpp)                     | Code in `NAMES.cpp` interacts with server functionalities in `Server.hpp` for handling display of users in a chat channel.                                                                                                                                                 |
| [NICK.cpp](https://github.com/mourdani/ft_irc/blob/master/src/commands/NICK.cpp)                       | Code snippet in src/commands/NICK.cpp:** Updates user's nickname in Server. Main role: nickname change logic. Key features: interacts with User entity, processes nickname change request.                                                                                 |

</details>

---

## 🚀 Getting Started

1. Clone the ft_irc repository:

```sh
git clone https://github.com/mourdani/ft_irc
```

2. Change to the project directory:

```sh
cd ft_irc
```

3. Install the dependencies:

```sh
g++ -o myapp main.cpp
```

4. Run the server
```sh
./ft_irc <port>
```
5. Connect to the server using an IRC client

[**Return**](#-quick-links)

---
