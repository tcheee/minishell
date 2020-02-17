#include "libft.h"

static int	ft_words_l(char const *s)
{
	int i;

	i = 0;
	while (s[i] >= 33 && s[i] != '\0')
		i++;
	i++;
	return (i);
}

static int	ft_count_w(char const *s)
{
	int i;
	int count_word;
	int is_word;

	i = 0;
	count_word = 0;
	is_word = 0;
	while (s[i])
	{
		if (s[i] >= 33 && is_word == 0)
		{
			is_word = 1;
			count_word++;
		}
		else if (s[i] < 33 && is_word == 1)
			is_word = 0;
		i++;
	}
	count_word++;
	return (count_word);
}

char		**ft_space_split(char const *s)
{
	int		n;
	int		i;
	int		j;
	char	**tab;

	n = -1;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * ft_count_w(s))))
		return (NULL);
	while (s[++n])
		if (s[n] >= 33)
		{
			if (!(tab[i] = (char*)malloc(sizeof(char) * ft_words_l(&s[n]))))
				return (NULL);
			while (s[n] >= 33 && s[n])
				tab[i][j++] = s[n++];
			tab[i++][j] = '\0';
			j = 0;
			n--;
		}
	tab[i] = NULL;
	return (tab);
}
