#include "../includes/minishell.h"

static int		check_builtin(char *word, char **words, char *buff)
{
	if (ft_strcmp(word, "env") == 0)
	{
		if (ft_env() == 0)
			return (0);
	}
	else if (ft_strcmp (word, "cd") == 0)
	{
		if (ft_chdir(words) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "echo") == 0)
		if (ft_echo(word, buff) == 0)
			return (0);
	return (-1);
}


static int		exec_command(char *word, char **words, char *buff)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char *command;
	if (check_builtin(word, words, buff) == 0)
		return (0);
	command = ft_strcat("/bin/", word); // need to set up the path
	pid = fork();
	if (pid == 0)
	{
		if (execve(command, words, g_env) == -1)
		{
			ft_printf("%s: command not found\n", word);
			//kill(pid, SIGTERM); // verif en cas d'erreur command not found que fonctionne bien
			exit(-1);
		};
	}
	else if (pid < 0)
	{
		ft_putstr("Error: fork did not work.\n");
		return (-1);
	}
	while (1)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return (0);
	}
	//free(PATH);
	return (0);
}

static int		check_quote(char *buff)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (buff[i] != '\0')
	{
		//if (buff[i] == ''') // how?
		//	j++;
		if (buff[i] == '"')
			k++;
		i++;
	}
	if ((k > 0 && k % 2 != 0) || (j > 0 && j % 2 != 0))
	{
		ft_putstr("Error: problem with the quotes. Try again.");
		return (-1);
	}
	return (0);
}

int				ft_analyse_input(char *buff)
{
	char **words;
	int i;

	if (check_quote(buff) == -1)
		return (-1);
	if (ft_strcmp(buff, QUIT_SHELL) == 0)
		return (1);
	i = 0;
	while (buff[i] != '\0')
		i++;
	if (ft_strlen(buff) == 1 && buff[i - 1] == '\n')
		return (0);
	else if (buff[i - 1] == '\n' && ft_strlen(buff) > 1)
		buff[i - 1] = '\0';
	words = ft_strsplit(buff, ' '); // to free
	exec_command(words[0], words, buff);
	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}
