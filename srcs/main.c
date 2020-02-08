#include "../includes/minishell.h"

void ft_mem_realloc(char **buff, int s, int i)
{
	char *tmp;

	s *= 2;
	if (!(tmp = malloc(sizeof(char *) * s))) // to free
		return;
	ft_memcpy(tmp, *buff, i);
	free(*buff);
	if (!(*buff = malloc(sizeof(char *) * s))) // to free
		return;
	ft_memcpy(*buff, tmp, i);
	free(tmp);
}

void ft_get_input(char **buff)
{
	int z;
	int s;
	int i;
	char *tmp;
	char buffer[SIZE];

	i = 0;
	s = SIZE;
	while ((*buff)[i] != '\n' && (*buff)[i] != EOF) // need to work with EOF
	{
		ft_printf("%d et buff: %s\n", i, *buff);
		z = 0;
		if ((z = read(0, buffer, SIZE)) == -1)
			return;
		i += z + 1;
		tmp = ft_strcat(*buff, buffer);
		(tmp)[i] = '\0';
		free(*buff);
		*buff = tmp;
		if (i >= s)
			ft_mem_realloc(buff, s, i);
	}
}

//clean out
//

int main(int ac, char **av, char **envp)
{
	char *buff;
	char **g_env;

	g_env = NULL;
	if (ac == 1 && av[0] != NULL)
	{
		ft_create_env(envp, &g_env);
		while (1)
		{
			if (!(buff = malloc(sizeof(char *) * SIZE))) // to free
				return (-1);
			buff[0] = '\0';
			//system ("leaks minishell"); // to check leaks
			ft_putstr("$> ");
			ft_get_input(&buff);
			if (ft_analyse_input(buff, &g_env) == 1) // clean out
			{
				free(buff);
				ft_putstr("See you!\n");
				ft_delete_env(&g_env);
				return(0);
			}
			free(buff);
		}
	}
	else 
		ft_putstr("Error: remove arguments to launch minishell. Try again.");
	return (0);
}
