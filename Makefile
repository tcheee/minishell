NAME = minishell

NAMELIB = ./libprint/libftprintf.a

CC = @gcc

CFLAGS =-Wall -Wextra -Werror

SRCS =	 	srcs/main.c\
			srcs/ft_analyze_input.c\

INCS = minishell.h

LIBDIR = ./libprint/
INCDIR = ./includes/

OBJ = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[33mCompiling...\033[0m"
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(NAMELIB)
	@echo "\033[32m$(NAME) compiled ✔ ✔ ✔ ✔\033[0m"

objs/%.o : srcs/%.c
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -I./includes -o $@

clean :
	@rm -rf $(OBJ) objs
	@make -C $(LIBDIR) clean
	@echo "\033[31mObjects deleted ✕\033[0m"

fclean : clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean
	@echo "\033[31m$(NAME) deleted ✕\033[0m"

re : fclean all

.PHONY : all clean fclean re
