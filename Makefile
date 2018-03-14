
NAME = test

SRC = ../voxGL/*.cpp *.cpp ../debugTools/*.cpp

PROJECT = actualProjectFolder

FRAMEWORKS = -framework OpenGl

GLFW_INC = -I ~/.brew/include

GLFW_LINK = -L ~/.brew/lib -lglfw

MY_INC = -I ../voxGL/. -I ../debugTools/.

FLAGS = -Wfatal-errors -std=c++11 -O3

make:
	(cd $(PROJECT); g++ -g $(FLAGS) $(SRC) -o $(NAME) \
$(FRAMEWORKS) $(MY_INC) $(GLFW_INC) $(GLFW_LINK))
	mv $(PROJECT)/$(NAME) .
	mv $(PROJECT)/$(NAME).dSYM .
fclean:
	rm $(NAME)
	rm -rf $(NAME).dSYM
