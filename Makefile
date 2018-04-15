# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/04/08 22:59:25 by twalton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bomberman
LIST = main \
ShadingProgram \
Time \
Window \
Camera \
Particles \
Engine \
TestState \
Model \
ObjFile \
ObjFileArrayExtractor \
BMPFileParse \
Light

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .cpp, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))

CPPFLAGS = -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter \
$(shell pkg-config --cflags glfw3 glm) \
-I lib/entityx \
-g -O3 -march=native

LDFLAGS = -framework OpenGl $(shell pkg-config --libs glfw3 glm) \
-L lib/entityx/entityx -lentityx \

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "\033[32;1mLinking.. \033[0m"
	@clang++ $(LDFLAGS) -o $@ $^
	@echo "\033[32;1m"$(NAME)" created\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(CPPFLAGS) -c -o $@ $<

clean:
	@echo "\033[31;1mCleaning..\033[0m"
	@rm -f $(OBJ)

fclean:
	@echo "\033[31;1mFull Cleaning..\033[0m"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@rm -rf lib

re:	fclean deps all

deps:
	@./deps.sh

.PHONY: clean fclean all re docs
