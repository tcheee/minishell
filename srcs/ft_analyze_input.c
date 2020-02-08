/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:46:05 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/08 19:37:21 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				check_builtin(char *word, char **words, char *buff, char ***env)
{
	if (ft_strcmp(word, "env") == 0)
	{
		if (ft_env(env, words) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "setenv") == 0) // error si name contient un "="
	{
		if (ft_setenv(words, env) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "unsetenv") == 0)
	{
		if (ft_unsetenv(words, env) == 0)
			return (0);
	}
	else if (ft_strcmp (word, "cd") == 0)
	{
		if (ft_chdir(words, env) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "echo") == 0)
		if (ft_echo(word, buff, words, env) == 0)
			return (0);
	return (-1);
}

static int		check_quote(char *buff)
{
	int i;
	int k;
	int c;

	c = 0;
	i = 0;
	k = 0;
	while (buff[i] != '\0')
	{
		if (c == 0 && (buff[i] == 39 || buff[i] == '"'))
			c = buff[i];
		if (buff[i] == c)
			k++;
		i++;
	}
	if ((k > 0 && k % 2 != 0))
	{
		ft_putstr("Error: problem with the quotes. Try again.\n");
		return (-1);
	}
	return (0);
}

int				ft_analyse_input(char *buff, char ***env)
{
	char **words;
	int i;

	if (check_quote(buff) == -1)
		return (-1);
	if (ft_strcmp(buff, QUIT_SHELL) == 0)
		return (1);
	i = 0;
	while (buff[i] != '\0')
		i++;
	if (ft_strlen(buff) == 1 && buff[i - 1] == '\n')
		return (0);
	else if (buff[i - 1] == '\n' && ft_strlen(buff) > 1)
		buff[i - 1] = '\0';
	words = ft_strsplit(buff, ' '); // to free
	exec_command(words[0], words, buff, env);
	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words[i]);
	free(words);
	return (0);
}
