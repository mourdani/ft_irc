# Folders and Names
NAME		= ircserv
SRCDIR		= src/
OBJDIR		= obj/
INCLUDES	= includes/
SRC			= main.cpp \
			User.cpp \
			Canal.cpp \
			Server.cpp \
			commands/command_handler.cpp \
			commands/JOIN.cpp \
			commands/NICK.cpp \
			commands/USER.cpp \
			commands/WHOIS.cpp \
			commands/PART.cpp \
			commands/LIST.cpp \
			commands/PRIVMSG.cpp \
			commands/QUIT.cpp \
			commands/PING.cpp  \
			commands/NAMES.cpp \
			commands/DIE.cpp \
			commands/TOPIC.cpp \
			commands/KICK.cpp \
			commands/OPER.cpp \
			commands/NOTICE.cpp \
			commands/PASS.cpp 
DEP			= $(OBJS:.o=.d)

# Compiler options
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -g -std=c++98

OBJ			= $(patsubst %.cpp, %.o, $(SRC))
OBJS		= $(addprefix ${OBJDIR}, ${OBJ})


all: $(NAME)

$(NAME): $(OBJS)
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Linking "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"

	@$(CC) -o $@ $(OBJS)

-include $(DEP)


$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@make create_dir_objs --no-print-directory
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Compiling "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"

	@$(CC) $(LFLAGS) $(CFLAGS) -MMD -MP -c -I $(INCLUDES) -o $@ $<

create_dir_objs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/commands
	@mkdir -p $(OBJDIR)/utils

clean:
	@rm -fr $(OBJDIR)
	@rm	-f ${DEP}
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "clean done"

fclean: clean
	@rm -rf $(NAME)
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "fclean done"

re: fclean all

test: all
	./$(NAME)

print_name:
	@tput bold
	@tput setaf 208
	@printf "%-10s " $(NAME)

.PHONY: all clean fclean re test print_name create_dir_objs
