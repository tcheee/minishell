#include "../includes/minishell.h"

static int		ft_existing_env(char *str, char ***env)
{
	char var[500];
	int k;
	int j;

	k = 0;
	while((*env)[k] != NULL)
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
			return (1);
		k++;
	}
	return (0);
}


static int		ft_check_format(char **words, int b)
{
	int i;

	i = 0;
	while (words[i] != NULL)
		i++;
	if (b == 1 && i != 3)
	{
		ft_putstr("Please use only two arguments: setenv VAR VALUE\n");
		return (-1);
	}
	else if (b == 0 && i != 2)
	{
		ft_putstr("Please use only two arguments: unsetenv VAR VALUE\n");
		return (-1);
	}
	return (0);
}

int		ft_modify_env(char ***env, char *var, char *value, int b)
{
	char **tmp;
	char *tmp2;
	int i;
	int n;
	b = 1;

	n = 0;
	while((*env)[n] != NULL)
		n++;
	
	if (!(tmp = (char**)malloc(sizeof(char**) * (n + 1)))) // to free
		return (-1);
	i = 0;
	while ((*env)[i] != NULL)
	{
		ft_printf("1) index: %d and content %s\n", i, (*env)[i]);
		if(!(tmp[i] = (char*)malloc(sizeof(char*) * (ft_strlen((*env)[i]) + 1)))) // to free
			return (-1);
		ft_memcpy(tmp[i], (*env)[i], ft_strlen((*env)[i]) + 1);
		free((*env)[i]);
		i++;
	}
	tmp[i] = NULL;
	free((*env)[i]);
	free(*env);

	if (!(*env = (char**)malloc(sizeof(char**) * (n + 1)))) // to free
		return (-1);
	i = 0;
	while (tmp[i] != NULL)
	{
		ft_printf("2) index: %d and content %s\n", i, (tmp)[i]);
		if(!((*env)[i] = (char*)malloc(sizeof(char*) * (ft_strlen(tmp[i]) + 1)))) // to free
			return (-1);
		ft_memcpy((*env)[i], tmp[i], ft_strlen(tmp[i]) + 1);
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(tmp);

	int j;
	int k;
	k = 0;
	j = 0;
	if (!(tmp2 = (char*)malloc(sizeof(char*) * (ft_strlen(var) + ft_strlen(value) + 2)))) // to free
		return (-1);
	while (var[j] != '\0')
	{
		tmp2[j] = var[j];
		j++;
	}
	tmp2[j] = '=';
	j++;
	while (value[k] != '\0')
	{
		tmp2[j] = value[k];
		j++;
		k++;
	}
	tmp2[j] = '\0';

	if(!((*env)[i] = (char*)malloc(sizeof(char*) * ((ft_strlen(tmp2) + 1))))) // to free
		return (-1);
	ft_memcpy((*env)[i], tmp2, ft_strlen(tmp2) + 1);
	free(tmp2);
	i++;
	(*env)[i] = NULL;

	return (0);
}

int		ft_setenv(char **words, char ***env)
{
	printf("enter here\n");
	if (ft_check_format(words, 1) == -1)
		return (0);
	if (ft_existing_env(words[1], env) == 1)
		ft_putstr("This variable already exist.\n");
	else
	{
		printf("word1: %s et word2: %s\n", words[1], words[2]);
		ft_modify_env(env, words[1], words[2], 0);
	}
	return(0);
}

int		ft_unsetenv(char **words, char ***env)
{
	if (ft_check_format(words, 0) == -1)
		return (0);
	if (ft_existing_env(words[1], env) == 0)
		ft_putstr("This variable does not exist.\n");
	else
	{
		ft_modify_env(env, words[1], NULL, 1);
	}
	return (0);
}
