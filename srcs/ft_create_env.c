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

int		ft_existing_env(char *str, char ***env)
{
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
			return (k);
		}
		k++;
	}
	free(var);
	return (-4);
}


int			ft_read_env(char *str, char **tmp, char ***env)
{
	char *var;
	int k;
	int j;
	int n;

	k = 0;
	if (!(var = (char*)malloc(sizeof(char*) * (2000)))) // to free
		return (-1);
	while((*env)[k] != NULL)
	{
		j = 0;
		n = 0;
		while ((*env)[k][j] != '\0' && (*env)[k][j] != '=')
		{
			var[j] = (*env)[k][j];
			j++;
		}
		var[j] = '\0';
		j++;
		if (ft_strcmp(ft_capitalize(str), ft_capitalize(var)) == 0)
		{
			while ((*env)[k][j] != '\0')
			{
				(*tmp)[n] = (*env)[k][j];
				j++;
				n++;
			}
			(*tmp)[n] = '\0';
			free(var);
			return (0);
		}
		k++;
	}
	free(var);
	return (-1);
}

int				ft_create_env(char **envp, char ***g_env)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	if (!(*g_env = (char**)malloc(sizeof(char**) * (i + 1)))) // to free
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		if(!((*g_env)[i] = (char*)malloc(sizeof(char*) * (ft_strlen(envp[i]) + 1)))) // to free
			return (-1);
		ft_memcpy((*g_env)[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	(*g_env)[i] = NULL;
	return (0);
}

int				ft_delete_env(char ***env) // to free
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
