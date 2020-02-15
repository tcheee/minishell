/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:46:24 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/15 15:46:52 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_env(char ***env, char **words)
{
	int j;
	int i;

	j = 0;
	while (words[j] != NULL)
		j++;
	if (j != 1)
	{
		ft_putstr("Please don't put argument after, just use: env\n");
		return (0);
	}
	i = 0;
	while ((*env)[i] != NULL)
	{
		ft_printf("%s\n", (*env)[i]);
		i++;
	}
	return (0);
}

int				ft_create_env(char **envp, char ***g_env)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	if (!(*g_env = (char**)malloc(sizeof(char**) * (i + 1))))
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!((*g_env)[i] = (char*)malloc(sizeof(char*)
						* (ft_strlen(envp[i]) + 1))))
			return (-1);
		ft_memcpy((*g_env)[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	(*g_env)[i] = NULL;
	return (0);
}

int				free_tab(char ***env)
{
	int i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		free((*env)[i]);
		i++;
	}
	free((*env)[i]);
	free(*env);
	return (0);
}

static void		create_new_elem(char ***new, char *tmp, int *i)
{
	(*new)[*i] = ft_strdup(tmp);
	(*i)++;
}

char			**realloc_env(char ***env, int n, char *tmp, int k)
{
	char	**new;
	int		i;
	int		j;

	if (!(new = (char**)malloc(sizeof(char**) * (n + 1))))
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
		create_new_elem(&new, tmp, &i);
	new[i] = NULL;
	free(*env);
	return (new);
}
