EXEC_NAME_FT = ircserv
PROJECT_NAME = ft_irc

SOURCES_FOLDER = ./srcs
INCLUDES_FOLDER = includes/

SOURCES_FILES = srcs/main.cpp \
				srcs/User/User.cpp \
				srcs/Command/CommandManager.cpp \
				srcs/Command/cmds/PASS.cpp \
				srcs/Command/cmds/NICK.cpp \
				srcs/Command/cmds/USER.cpp \
				srcs/Command/cmds/QUIT.cpp \
				srcs/Command/cmds/MODE.cpp \
				srcs/Command/cmds/PING.cpp \
				srcs/Command/cmds/JOIN.cpp \
				srcs/Command/cmds/PART.cpp \
				srcs/Command/cmds/WHO.cpp \
				srcs/Command/cmds/OPER.cpp \
				srcs/Command/cmds/PRIVMSG.cpp \
				srcs/Command/cmds/KICK.cpp \
				srcs/Command/rfc/replies.cpp \
				srcs/Channel/Channel.cpp \
				srcs/Server.cpp

OBJECTS_FILES_FT = $(patsubst $(SOURCES_FOLDER)%.cpp, $(OBJECTS_FOLDER)%_ft.o, $(SOURCES_FILES))

OBJECTS_FOLDER = ./objs/

INCLUDES_FLAGS = -I $(INCLUDES_FOLDER) 


CC = clang++
CFLAGS =  -g3 #-Wall -Wextra -Werror

all: $(EXEC_NAME_FT)

$(EXEC_NAME_FT): $(OBJECTS_FILES_FT)
	$(CC) $(CFLAGS) $(INCLUDES_FLAGS) $(OBJECTS_FILES_FT) -o $(EXEC_NAME_FT) -D TESTED_NAMESPACE=ft


$(OBJECTS_FOLDER)%_ft.o: $(SOURCES_FOLDER)/%.cpp
	@mkdir -p $(OBJECTS_FOLDER)
	$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -I srcs/User/User.hpp  -I srcs/Command/CommandManager.hpp -c $< -o $@ -D TESTED_NAMESPACE=ft

clean:
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@rm -rf $(EXEC_NAME_FT)
	@echo "clean"

re: fclean all

.PHONY: all clean fclean re