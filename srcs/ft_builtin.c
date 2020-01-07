#include "../includes/minishell.h"

static int		ft_capitalize(char **str)
{
	int i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] >= 97 && (*str)[i] <= 122)
			(*str)[i] = (*str)[i] - 32;
		i++;
	}
	return (0);
}

int				ft_echo(char *word, char *buff, char **words)
{
	int j;
	char *tmp;
	char c;

	c = 0;
	if (words[1] && words[1][0] == '$')
	{
		if (!(tmp = malloc(sizeof(char*) * 1024)))
			return (-1);
		ft_capitalize(&words[1]);
		if (ft_read_env(&words[1][1], &tmp) == -1)
			ft_putstr("\n");
		else
			ft_printf("%s\n", tmp);
		free(tmp);
	}
	else
	{
		j = ft_strlen(word);
		while (buff[j] != '\0')
		{
			while (buff[j] == 32)
				j++;
			if (c == 0 && (buff[j] == '"' || buff[j] == 39))
				c = buff[j];
			if (buff[j] == c)
			{
				j++;
				while (buff[j] != c && buff[j] != '\0')
				{
					ft_putchar(buff[j]);
					j++;
				}
			}
			else 
			{
				while (buff[j] != ' ' && buff[j] != c && buff[j] != '\0')
				{
					ft_putchar(buff[j]);
					j++;
				}
				if (buff[j] == ' ')
					ft_putchar(' ');
			}
		}
		ft_putstr("\n");
	}
	return (0);
}

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
		if (!(tmp = malloc(sizeof(char*) * 1024)))
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
