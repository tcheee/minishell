#include "../includes/minishell.h"

static int		ft_existing_env(char *str, char ***env)
{
	// bug here
	char var[500];
	int k;
	int j;

	k = 0;
	ft_putstr("bug?\n");
	while((*env)[k] != NULL)
	{
		ft_putstr("loop\n");
		j = 0;
		while ((*env)[k][j] != '\0' && (*env)[k][j] != '=')
		{
			var[j] = (*env)[k][j];
			j++;
		}
		var[j] = '\0';
		j++;
		if (ft_strcmp(str, var) == 0)
		{
			var[0] = '\0';
			return (1);
		}
		k++;
	}
	var[0] = '\0';
	ft_putstr("out of loop\n");
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

int		ft_modify_env(char ***env, char *var, char *value)
{
	ft_printf("ici1\n");
	char **tmp;
	char *new_env;
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	j = 0;
	if (!(new_env = (char*)malloc(sizeof(char*) * (ft_strlen(var) + ft_strlen(value) + 2)))) // to free
		return (-1);
	ft_printf("ici2\n");
	while (var[j] != '\0')
	{
		new_env[j] = var[j];
		j++;
	}
	new_env[j] = '=';
	j++;
	while (value[k] != '\0')
	{
		new_env[j] = value[k];
		j++;
		k++;
	}
	new_env[j] = '\0';

	ft_printf("ici3\n");	
	tmp = NULL;
	i = 0;
	while((*env)[i] != NULL)
		i++;
	
	if (!(tmp = (char**)malloc(sizeof(char**) * (i + 1)))) // to free
	{
		ft_putstr("probleme malloc\n");
		return (-1);
	}
	i = 0;
	while ((*env)[i] != NULL)
	{
		ft_printf("1) index: %d and content %s\n", i, (*env)[i]);
		if(!(tmp[i] = (char*)malloc(sizeof(char*) * (ft_strlen((*env)[i]) + 1)))) // to free
		{
			ft_putstr("probleme malloc\n");
			return (-1);
		}
		memcpy(tmp[i], (*env)[i], ft_strlen((*env)[i]) + 1);
		free((*env)[i]);
		i++;
	}
	free((*env)[i]);
	free(*env);
	ft_printf("ici4\n");	

	if(!(tmp[i] = (char*)malloc(sizeof(char*) * ((ft_strlen(new_env) + 1))))) // to free
		return (-1);
	ft_memcpy(tmp[i], new_env, ft_strlen(new_env) + 1);
	free(new_env);
	i++;
	tmp[i] = NULL;
	*env = tmp;

	return (0);
}

int		ft_setenv(char **words, char ***env)
{
	ft_putstr("enter ici\n");
	if (ft_check_format(words, 1) == -1)
		return (0);
	if (ft_existing_env(words[1], env) == 1)
		ft_putstr("This variable already exist.\n");
	else
	{
		ft_putstr("go to modify!\n");
		printf("word1: %s et word2: %s\n", words[1], words[2]);
		ft_modify_env(env, words[1], words[2]);
	}
	return(0);
}

int		ft_unsetenv(char **words, char ***env)
{
	if (ft_check_format(words, 0) == -1)
		return (0);
	if (ft_existing_env(words[1], env) == 0)
		ft_putstr("This variable does not exist.\n");
	return (0);
}
