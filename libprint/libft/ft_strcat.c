/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:07:06 by ayguillo          #+#    #+#             */
/*   Updated: 2020/02/08 17:47:39 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(char *s1, const char *s2)
{
	int len;

	if (s1 && s2)
		len = ft_strlen(s1) + ft_strlen(s2);
	else if (s1)
		len = ft_strlen(s1);
	else if (s2)
		len = ft_strlen(s2);
	else
		return (0);
	return (len);
}

char		*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	len = get_len(s1, s2);
	if (!(tmp = malloc(sizeof(*tmp) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[j] != '\0')
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = '\0';
	return (tmp);
}
