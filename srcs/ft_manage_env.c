#include "../includes/minishell.h"

int		ft_setenv(char **words)
{
	char *tmp;

	if (!(tmp = malloc(sizeof(char*) * 1024))) // delete
		return (-1);
	ft_read_env(words[1], &tmp);
	ft_printf("%s\n", tmp);
	return(0);
}

int		ft_unsetenv(char **words)
{
	char *tmp;

	if (!(tmp = malloc(sizeof(char*) * 1024))) // delete
		return (-1);
	ft_read_env(words[1], &tmp);
	ft_printf("%s\n", tmp);
	return (0);
}
