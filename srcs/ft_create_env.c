#include "../includes/minishell.h"

int				ft_env(char ***env)
{
	int i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		ft_printf("%s\n", (*env)[i]);
		i++;
	}
	return (0);
}


int			ft_read_env(char *str, char **tmp, char ***env)
{
	char var[500];
	int k;
	int j;
	int n;

	k = 0;
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
		if (ft_strcmp(str, var) == 0)
		{
			while ((*env)[k][j] != '\0')
			{
				(*tmp)[n] = (*env)[k][j];
				j++;
				n++;
			}
			(*tmp)[n] = '\0';
			return (0);
		}
		k++;
	}
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

//int				ft_delete_env() // to free
