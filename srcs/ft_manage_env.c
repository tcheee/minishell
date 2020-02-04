#include "../includes/minishell.h"


static int		ft_existing_env(char *str, char ***env)
{
	// bug here
	char	*var;
	int		k;
	int		j;

	if (!(var = (char*)malloc(sizeof(char*) * (2000)))) // to free
		return (-1);
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
		{
			free(var);
			return (1);
		}
		k++;
	}
	free(var);
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

static char	**realloc_env(char ***env, int n, char *tmp)
{
	char	**new;
	int		i;

	ft_printf("%s\n", tmp);
	if (!(new = (char**)malloc(sizeof(char**) * (n + 1)))) // to free
		return (NULL);
	i = 0;
	while ((*env)[i] && i < n)
	{
		ft_printf("%d: %s\n", i, (*env)[i]);
		new[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	free(*env);
	new[i] = ft_strdup(tmp);
	i++;
	new[i] = NULL;
	return (new);
}

int		ft_modify_env(char ***env, char *var, char *value)
{
	ft_printf("ici1\n");
	char	*tmp1;
	char	*tmp2;
	int		n;

	
	tmp1 = ft_strcat(var, "=");
	tmp2 = ft_strcat(tmp1, value);
	n = 0;
	while ((*env)[n])
		n++;
	if ((*env = realloc_env(env, n + 1, tmp2)) == NULL)
		return (-1);
	free(tmp1);
	free(tmp2);
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
