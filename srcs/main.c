/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:45:39 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/08 20:09:18 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_mem_realloc(char **buff, int s, int i)
{
	char *tmp;

	s *= 2;
	if (!(tmp = malloc(sizeof(char *) * s)))
		return;
	ft_memcpy(tmp, *buff, i);
	free(*buff);
	if (!(*buff = malloc(sizeof(char *) * s)))
		return;
	ft_memcpy(*buff, tmp, i);
	free(tmp);
}

void ft_get_input(char **buff) // find a way to read size by size
{
	int s;
	int i;
	char l;

	i = 0;
	s = SIZE;
	while (42)
	{
		if (read(0, &l, 1) == -1)
			return ;
		if (l == '\n' || l == EOF)
		{
			(*buff)[i] = l;
			(*buff)[i + 1] = '\0';
			return ;
		}
		else 
			(*buff)[i] = l;
		i++;
		if (i >= SIZE)
			ft_mem_realloc(buff, s, i);
	}
}

static int	finish_minishell(char **buff, char ***env)
{
	free(*buff);
	ft_putstr("See you!\n");
	free_tab(env);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char *buff;
	char **g_env;

	g_env = NULL;
	buff = NULL;
	if (ac == 1 && av[0] != NULL)
	{
		ft_create_env(envp, &g_env);
		while (1)
		{
			if (!(buff = malloc(sizeof(char *) * SIZE))) // to free
				return (-1);
			buff[0] = '\0';
			ft_putstr("$> ");
			ft_get_input(&buff);
			if (ft_analyse_input(buff, &g_env) == 1) // clean out
			  return (finish_minishell(&buff, &g_env));
			free(buff);
		}
	}
	else 
		ft_putstr("Error: remove arguments to launch minishell. Try again.");
	return (0);
}
