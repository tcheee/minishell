#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libprint/includes/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define SIZE 4
# define QUIT_SHELL "exit\n"

# define COLOR_RESET	"\033[0m"
# define BOLD			"\033[1m"
# define BLACK_TEXT		"\033[30;1m"
# define RED_TEXT		"\033[31;1m"
# define GREEN_TEXT		"\033[32;1m"
# define YELLOW_TEXT	"\033[33;1m"
# define BLUE_TEXT		"\033[34;1m"
# define MAGENTA_TEXT	"\033[35;1m"
# define CYAN_TEXT		"\033[36;1m"
# define WHITE_TEXT		"\033[37;1m"

char **env;

int		ft_analyse_input(char *buff);
int		ft_create_env(char **envp, char **env);

#endif
