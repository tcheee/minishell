#include "../includes/minishell.h"

static void		ft_increment(char c, int *j)
{
	ft_putchar(c);
	(*j)++;
}

int				ft_echo(char *word, char *buff) // implement '
{
	int j;
	//char c;

	// implement character c
	j = ft_strlen(word);
	while (buff[j] != '\0')
	{
		while (buff[j] == 32)
			j++;
		if (buff[j] == '"')
		{
			
			j++;
			while (buff[j] != '"' && buff[j] != '\0')
				ft_increment(buff[j], &j);
		}
		else 
		{
			while (buff[j] != ' ' && buff[j] != '"' && buff[j] != '\0')
				ft_increment(buff[j], &j);
			if (buff[j] == ' ')
				ft_putchar(' ');
		}
	}
	ft_putstr( "\n");
	return (0);
}

static int		check_dir(char **words, int i)
{
}

int				ft_chdir(char **words)
{
	char *tmp;
	int i;

	i = 0;
	while (words[i] != NULL)
		i++;
	if (check_dir(words, i) == -1) // create a check of the words
 		return (0);
	if (i == 1 || ft_strcmp(words[1], "~") == 0)
	{
		if (!(tmp = malloc(sizeof(char*) * 1024)))
			return (-1);
		if (ft_read_env("HOME", &tmp) == -1)
			return (-1);
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(words[1]);
	return (0);
}
