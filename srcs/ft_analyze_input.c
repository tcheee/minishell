#include "../includes/minishell.h"

int		exec_command(char *command, char **words)
{
	// manage /bin/ directly
	char *PATH;
	extern char **environ;

	//check_builtin function
	PATH = ft_strcat("/bin/", command); // to free
	if (execve(PATH, words, environ) == -1) // need to set up the environ variable
	{
		ft_putstr("error\n");
	};
	free(PATH);
	return (0);
	
}


int     ft_analyse_input(char *buff)
{
	char **words;
	int i;
	char *command;

	i = 0;
	words = ft_strsplit(buff, ' '); // to free
	command = words[0];
	ft_printf("The command is : %s\n", command);
	exec_command(command, words);
	while (words[i] != NULL)
	{
		ft_printf("%s\n", words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
