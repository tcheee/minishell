/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:46:30 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/08 18:46:31 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_capitalize(char *str)
{
	int i;

	i = 0;
	while ((str)[i] != '\0')
	{
		if ((str)[i] >= 97 && (str)[i] <= 122)
			(str)[i] = (str)[i] - 32;
		i++;
	}
	return (str);
}

int				ft_echo(char *word, char *buff, char **words, char ***env)
{
	int j;
	char *tmp;
	char c;

	c = 0;
	if (words[1] && words[1][0] == '$')
	{
		if (!(tmp = malloc(sizeof(char*) * 2048)))
			return (-1);
		if (ft_read_env(&words[1][1], &tmp, env) == -1)
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
