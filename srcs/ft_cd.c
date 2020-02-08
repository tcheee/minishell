/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:46:17 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/08 19:42:46 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int		change_dir(char **words, char ***env, int b)
{
	char *tmp;
	char *temp;

	tmp = NULL;
	temp = NULL;
	if (!(tmp = malloc(sizeof(char*) * 2048)))
		return (-1);
	if (ft_read_env("HOME", &tmp, env) == -1)
		return (-1);
	if (b != 1 && ft_strlen(words[1]) > 1)
		temp = ft_strcat(tmp, &words[1][1]);
	chdir(tmp);
	free(temp);
	free(tmp);
	return (0);
}

int				ft_chdir(char **words, char ***env) // voir si plus propre pour tmp?
{
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
		if (change_dir(words, env, b) == -1)
			return (-1);
	}
	else
		chdir(words[1]);
	return (0);
}
