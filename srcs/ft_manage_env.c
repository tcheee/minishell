/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:46:35 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/08 18:46:36 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_check_format(char **words, int b)
{
	int i;

	i = 0;
	while (words[i] != NULL)
		i++;
	if (b == 1 && i != 3)
	{
		ft_putstr("Please use two arguments: setenv VAR VALUE\n");
		return (-1);
	}
	else if (b == 0 && i != 2)
	{
		ft_putstr("Please use two arguments: unsetenv VAR VALUE\n");
		return (-1);
	}
	return (0);
}

static char	**realloc_env(char ***env, int n, char *tmp, int k)
{
	char	**new;
	int		i;
	int		j;

	if (!(new = (char**)malloc(sizeof(char**) * (n + 1)))) // to free
		return (NULL);
	i = 0;
	j = 0;
	while ((*env)[i] != NULL && (*env)[j] && i < n)
	{
		if (i == k)
		{	
			free((*env)[i]);
			j++;
		}
		new[i] = (*env)[j];
		i++;
		j++;
	}
	if (tmp != NULL)
	{
		new[i] = ft_strdup(tmp);
		tmp[ft_strlen(tmp)] = '\0';
		i++;
	}
	new[i] = NULL;
	free(*env);
	return (new);
}

int			ft_modify_env(char ***env, char *new_env, int k)
{
	int		n;

	n = 0;
	while ((*env)[n])
		n++;
	if (k >= 0)
		n--;
	if ((*env = realloc_env(env, n + 1, new_env, k)) == NULL)
		return (-1);
	return (0);
}

int			ft_setenv(char **words, char ***env)
{
	char	*tmp1;
	char	*tmp2;
	int		k;

	if (ft_check_format(words, 1) == -1)
		return (0);
	tmp1 = ft_strcat(words[1], "=");
	tmp2 = ft_strcat(tmp1, words[2]);
	if ((k = ft_existing_env(words[1], env)) >= 0)
	{
		free((*env)[k]);
		(*env)[k] = ft_strdup(tmp2);
	}
	else
		ft_modify_env(env, tmp2, -4);
	free(tmp1);
	free(tmp2);
	return(0);
}

int			ft_unsetenv(char **words, char ***env)
{
	int k;

	if (ft_check_format(words, 0) == -1)
		return (0);
	if ((k = ft_existing_env(words[1], env)) >= 0)
		ft_modify_env(env, NULL, k);
	return (0);
}
