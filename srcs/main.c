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
	char buffer[SIZE];

	i = 0;
	s = SIZE;
	while ((*buff)[i - 1] != '\n' && (*buff)[i - 1] != EOF) // need to work with EOF
	{
		z = 0;
		if ((z = read(0, buffer, SIZE)) == -1)
			return;
		i += z;
		*buff = ft_strcat(*buff, buffer);
		(*buff)[i] = '\0';
		if (i >= s)
			ft_mem_realloc(buff, s, i);
	}
}

int main(void)
{
	char *buff;

	buff = NULL;
	while (!buff || strcmp(buff, QUIT_SHELL) != 0)
	{
		if (!(buff = malloc(sizeof(char *) * SIZE))) // to free
			return (-1);
		buff[0] = '\0';
		ft_putstr("$> ");
		ft_get_input(&buff);
		ft_putstr(buff);
		ft_analyse_input(buff);
		free(buff);
	}
	ft_putstr("See you!");
	return (0);
}
