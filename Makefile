# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/04/19 14:05:41 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bomberman
LIST = main \
Window \
Time \
ShadingProgram \
Camera \
Sprite2D \
ObjFileArrayExtractor \
ObjFile \
Texture \
Model \
Light \
Particles \
systems \
generate_level \
Engine \
MenuState \
TestState \
ParticleExplosion \
Text \
Cells

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .cpp, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))

CPPFLAGS = -std=c++14 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-private-field \
$(shell pkg-config --cflags glfw3 glm) \
-I lib/entt/src \
-I lib/lodepng \
-g -O3 -march=native \

LDFLAGS = -framework OpenGl \
$(shell pkg-config --libs glfw3 glm) \
-L lib/lodepng -llodepng \

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "\033[34;1mCompiling: \033[0m"$<
	@clang++ $(CPPFLAGS) -c -o $@ $<

lib/lodepng/liblodepng.a: lib/lodepng/lodepng.cpp
	@echo "\033[35;1mCompiling Dependency: \033[0m"$<
	@clang++ $(CPPFLAGS) -c -o lib/lodepng/lodepng.o $<
	@ar rcs $@ lib/lodepng/lodepng.o

$(NAME): lib/lodepng/liblodepng.a $(OBJ)
	@echo "\033[32;1mLinking.. \033[0m"
	@clang++ $(LDFLAGS) -o $@ $^
	@echo "\033[32;1mCreated:\033[0m "$(NAME)

clean:
	@echo "\033[31;1mCleaning..\033[0m"
	@rm -f $(OBJ)
	@rm -f lib/lodepng/lodepng.o

fclean:
	@echo "\033[31;1mFull Cleaning..\033[0m"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@rm -f lib/lodepng/liblodepng.a

re:	fclean all

deps:
	@./deps.sh

.PHONY: clean fclean all re docs
