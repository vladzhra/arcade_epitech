##
## EPITECH PROJECT, 2022
## B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
## File description:
## Makefile
##

# Compiler and linker options
NAME	=	arcade
CC		=	g++
CXXFLAGS	+=	-Wall -Wextra -pedantic -std=c++20 -fPIC -I src/
LDFLAGS		=	-L./lib -ldl
CPPFLAGS	=	-I include
SFMLFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
NCURSESFLAGS	=	-lncurses
SDLFLAGS	=	-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Directories
SRC_DIR		=	src
LIB_DIR		=	lib
GRAPH_DIR	=	$(SRC_DIR)/graphics
GAMES_DIR	=	$(SRC_DIR)/games
CORE_DIR	=	$(SRC_DIR)/core

CORE_SRCS	=	$(SRC_DIR)/main.cpp \
				$(CORE_DIR)/Core.cpp
CORE_OBJS	=	$(CORE_SRCS:.cpp=.o)

all: graphicals games core finish

core:	$(NAME)

games:
	mkdir -p $(LIB_DIR)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -c $(GAMES_DIR)/arcade_snake.cpp -o $(GAMES_DIR)/arcade_snake.o
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -shared -o $(LIB_DIR)/arcade_snake.so $(GAMES_DIR)/arcade_snake.o
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -c $(GAMES_DIR)/arcade_nibbler.cpp -o $(GAMES_DIR)/arcade_nibbler.o
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -shared -o $(LIB_DIR)/arcade_nibbler.so $(GAMES_DIR)/arcade_nibbler.o
	@echo "\033[1;32mGames compilation successful!\033[0m"

graphicals:
	mkdir -p $(LIB_DIR)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -c $(GRAPH_DIR)/arcade_sfml.cpp -o $(GRAPH_DIR)/arcade_sfml.o $(SFMLFLAGS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -shared -o $(LIB_DIR)/arcade_sfml.so $(GRAPH_DIR)/arcade_sfml.o $(SFMLFLAGS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -c $(GRAPH_DIR)/arcade_ncurses.cpp -o $(GRAPH_DIR)/arcade_ncurses.o $(NCURSESFLAGS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -shared -o $(LIB_DIR)/arcade_ncurses.so $(GRAPH_DIR)/arcade_ncurses.o $(NCURSESFLAGS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -c $(GRAPH_DIR)/arcade_sdl2.cpp -o $(GRAPH_DIR)/arcade_sdl2.o $(SDLFLAGS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -shared -o $(LIB_DIR)/arcade_sdl2.so $(GRAPH_DIR)/arcade_sdl2.o $(SDLFLAGS)
	@echo "\033[1;32mGraphicals compilation successful!\033[0m"

$(NAME): $(CORE_OBJS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) -c $(SRCS) -o $(CORE_OBJS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(CPPFLAGS) $(CORE_OBJS) -ldl -o $(NAME)
	@echo "\033[1;32mCore compilation successful!\033[0m"

finish:
	@echo "\e[42;1m----------------READY TO WORK!----------------\e[0m"

clean:
	rm -f $(CORE_OBJS) $(GRAPH_OBJS) $(NAME)

fclean: clean
	rm -f $(GRAPH_DIR)/*.o $(LIB_DIR)/*.so $(GAMES_DIR)/*.o $(CORE_DIR).o

re: fclean all

.PHONY: all core graphicals games clean fclean re