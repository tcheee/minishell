#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libprint/includes/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>

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

char **g_env;

int		ft_analyse_input(char *buff);
int		ft_create_env(char **envp);
int		ft_env(void);
int		ft_echo(char *word, char *buff, char **words);
int		ft_chdir(char **words);
int		ft_read_env(char *str, char **tmp);
int		ft_setenv(char **words);
int		ft_unsetenv(char **words);

#endif
