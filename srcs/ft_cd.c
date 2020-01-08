#include "../includes/minishell.h"

static int		check_dir(char **words, int i)
{
	if (i == 1)
		return (0);
	if (i > 2 || (access(words[1], F_OK) == -1 && words[1][0] != '~'))
	{
		ft_printf("cd: no such file or directory: %s\n", words[1]);
		return (-1);
	}
	if (access(words[1], X_OK) == -1 && words[1][0] != '~')
	{
		ft_printf("cd: permission denied: %s\n", words[1]);
		return (-1);
	}
	return (0);
}

int				ft_chdir(char **words) // voir si plus propre pour tmp?
{
	char *tmp;
	int i;
	int b;

	b = 0;
	i = 0;
	while (words[i] != NULL)
		i++;
	if (check_dir(words, i) == -1)
		return (0);
	if (i == 1)
		b = 1;
	else if (words[1][0] == '~')
		b = 2;
	if (b != 0)
	{
		if (!(tmp = malloc(sizeof(char*) * 2048)))
			return (-1);
		if (ft_read_env("HOME", &tmp) == -1)
			return (-1);
		if (b != 1 && ft_strlen(words[1]) > 1)
			tmp = ft_strcat(tmp, &words[1][1]);
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(words[1]);
	return (0);
}
