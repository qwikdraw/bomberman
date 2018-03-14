
NAME = test

SRC = ../voxGL/*.cpp *.cpp ../debugTools/*.cpp

QUICKSRC = *.cpp

FRAMEWORKS = -framework OpenGl

GLFW_INC = -I ~/.brew/include

GLFW_LINK = -L ~/.brew/lib -lglfw

MY_INC = -I ../voxGL/. -I ../debugTools/.

QUICK_INC = -I .

FLAGS = -Wfatal-errors -std=c++11 -O3

make:
	g++ -g $(FLAGS) $(SRC) -o $(NAME) $(FRAMEWORKS) $(MY_INC) $(GLFW_INC) $(GLFW_LINK)

quick:
	g++ -g $(FLAGS) $(QUICKSRC) -o $(NAME) $(FRAMEWORKS) $(QUICK_INC) $(GLFW_INC) $(GLFW_LINK)

fclean:
	rm $(NAME)
	rm -rf $(NAME).dSYM
