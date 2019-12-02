#include "../includes/minishell.h"

int		ft_create_env(char **envp, char **env)
{
	int i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	//copier envp dans env avec malloc en comptant. Faire une liste chaine ou tableau rempli de NULL lors des unset? Pour setenv et unsetenv
	//split la variable PATH pour avoir les differents chemins possibles
	//
	return (0);
}
