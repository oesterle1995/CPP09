#Name
NAME = RPN


#Compilation
CC = c++
FLAG = -std=c++98 -Wall -Wextra -Werror -g
OPT_NAME = -o $(NAME)
OPT_HEADER = -I.

#clean
RM = rm -rf

#directories
OBJ_DIR = Obj
SRC = main.cpp RPN.cpp
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o )

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAG) $(OBJ)  $(OPT_NAME)
	@echo Succeed : Compilation

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAG) $(OPT_HEADER) -c $< -o $@
clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re