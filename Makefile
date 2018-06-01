# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/05/28 19:42:07 by ihodge           ###   ########.fr        #
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
build_level \
Engine \
MenuState \
GameState \
DeathState \
ParticleExplosion \
Text \
Cells \
powerups \
Effects \
scripts \
SettingState \
PauseState \
Sparkles

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .cpp, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)

CPPFLAGS = -std=c++14 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-private-field \
$(shell pkg-config --cflags glfw3 glm) \
-I lib/entt/src \
-I lib/lodepng \
-I lib/irrklang/include \
-g -O3 -march=native \
#-fsanitize=undefined -fsanitize=address

LDFLAGS = -framework OpenGl \
$(shell pkg-config --libs glfw3 glm) \
-L lib/lodepng -llodepng \
-L lib/irrklang -lirrklang -rpath '@executable_path/lib/irrklang' -pthread \
#-fsanitize=undefined -fsanitize=address

all: $(OBJ_DIR) $(NAME)

$(NAME): lib/lodepng/liblodepng.a $(OBJ)
	@printf "\e[32;1mLinking.. \e[0m\n"
	@clang++ $(LDFLAGS) -o $@ $^
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@clang++ $(CPPFLAGS) -MMD -c $< -o $@

lib/lodepng/liblodepng.a: lib/lodepng/lodepng.cpp
	@printf "\e[35;1mCompiling Dependency: \e[0m%s\n" $<
	@clang++ $(CPPFLAGS) -c -o lib/lodepng/lodepng.o $<
	@ar rcs $@ lib/lodepng/lodepng.o

clean:
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ)
	@rm -f lib/lodepng/lodepng.o

fclean:
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@rm -f lib/lodepng/liblodepng.a

re:	fclean all

deps:
	@./deps.sh

.PHONY: clean fclean all re docs
