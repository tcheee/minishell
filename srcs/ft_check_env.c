/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:08:00 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/15 15:19:22 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		location_elem_env(char **var, int k)
{
	free(*var);
	return (k);
}

int				ft_existing_env(char *str, char ***env)
{
	char	*var;
	int		k;
	int		j;

	if (!(var = (char*)malloc(sizeof(char*) * (2048))))
		return (-1);
	k = 0;
	while ((*env)[k] != NULL)
	{
		j = 0;
		while ((*env)[k][j] != '\0' && (*env)[k][j] != '=')
		{
			var[j] = (*env)[k][j];
			j++;
		}
		var[j] = '\0';
		j++;
		if (ft_strcmp(str, var) == 0)
			return (location_elem_env(&var, k));
		k++;
	}
	free(var);
	return (-4);
}

static void		loop1(char ***env, char **var, int *j, int k)
{
	(*var)[*j] = (*env)[k][*j];
	(*j)++;
}

static void		copy_elem_env(char ***env, char **tmp, int k, int j)
{
	int n;

	n = 0;
	while ((*env)[k][j] != '\0')
	{
		(*tmp)[n] = (*env)[k][j];
		j++;
		n++;
	}
	(*tmp)[n] = '\0';
}

int				ft_read_env(char *str, char **tmp, char ***env)
{
	char	*var;
	int		k;
	int		j;

	k = 0;
	if (!(var = (char*)malloc(sizeof(char*) * (2048)))) //block 2048 to avoid segfault
		return (-1);
	while ((*env)[k] != NULL)
	{
		j = 0;
		while ((*env)[k][j] != '\0' && (*env)[k][j] != '=')
			loop1(env, &var, &j, k);
		var[j] = '\0';
		j++;
		if (ft_strcmp(ft_capitalize(str), ft_capitalize(var)) == 0)
		{
			copy_elem_env(env, tmp, k, j);
			free(var);
			return (0);
		}
		k++;
	}
	free(var);
	return (-1);
}
