#include "../includes/minishell.h"

// To 
/*static int	create_new_node(list **tmp)
  {
  if (!(*tmp = (list*)malloc(sizeof(list))))
  return (-1);
  (*tmp)->elem = NULL;
  (*tmp)->next = NULL;
  return (0);
  }*/


/*int			ft_create_env(char **envp)
  {
  int i;
  list *tmp;

  g_env = NULL;
  i = 0;
  tmp = g_env;
  while (envp[i] != NULL)
  {
  if (create_new_node(&tmp) == -1)
  return (-1);
  if (!(tmp->elem = (char*)malloc(sizeof(char*) * ft_strlen(envp[i])))) // to free
  return (-1);
  ft_memmove(tmp->elem, envp[i], ft_strlen(envp[i]));
  ft_printf("%s\n", tmp->elem);
  i++;
  tmp = tmp->next;
  }
  return (0);
  }*/

int				ft_env(void)
{
	int i;

	i = 0;
	while (g_env[i] != NULL)
	{
		ft_printf("%s\n", g_env[i]);
		i++;
	}
	return (0);
}

int			ft_read_env(char *str, char **tmp)
{
	char var[500];
	int k;
	int j;
	int n;

	k = 0;
	while(g_env[k] != NULL)
	{
		j = 0;
		n = 0;
		while (g_env[k][j] != '\0' && g_env[k][j] != '=')
		{
			var[j] = g_env[k][j];
			j++;
		}
		var[j] = '\0';
		j++;
		if (ft_strcmp(str, var) == 0)
		{
			while (g_env[k][j] != '\0')
			{
				(*tmp)[n] = g_env[k][j];
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

int				ft_create_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	if (!(g_env = (char**)malloc(sizeof(char**) * (i + 1)))) // to free
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		if(!(g_env[i] = (char*)malloc(sizeof(char*) * (ft_strlen(envp[i]) + 1)))) // to free
			return (-1);
		ft_memcpy(g_env[i], envp[i], ft_strlen(envp[i]) + 1);
		//ft_printf("%s\n", g_env[i]);
		i++;
	}
	g_env[i] = NULL;
	return (0);
}
