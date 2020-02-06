#include "../includes/minishell.h"

static int		check_builtin(char *word, char **words, char *buff, char ***env)
{
	if (ft_strcmp(word, "env") == 0)
	{
		if (ft_env(env, words) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "setenv") == 0) // error si name contient un "="
	{
		if (ft_setenv(words, env) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "unsetenv") == 0)
	{
		if (ft_unsetenv(words, env) == 0)
			return (0);
	}
	else if (ft_strcmp (word, "cd") == 0)
	{
		if (ft_chdir(words, env) == 0)
			return (0);
	}
	else if (ft_strcmp(word, "echo") == 0)
		if (ft_echo(word, buff, words, env) == 0)
			return (0);
	return (-1);
}

static int		set_path(char *word, char **command, char ***env) // need to free ce path
{
	char *tmp;
	char *com;
	char *temp;
	char **split;
	int i;
	int l;

	i = 0;
	l = 0;
	if (!(tmp = malloc(sizeof(char*) * 2048)))
		return (-1);
	if (ft_read_env("PATH", &tmp, env) == -1)
		return (-1);
	split = ft_strsplit(tmp, ':'); // to free
	free(tmp);
	com = ft_strcat("/", word);
	while (split[i] != NULL)
	{
		temp = ft_strcat(split[i], com);
		if (access(temp, F_OK) == 0)
		{
			*command = temp;
			free(com);
			while (split[l] != NULL)
			{
				free(split[l]);
				l++;
			}
			free(split);
			return (0);
		}
		free(temp);
		i++;
	}
	free(com);
	return (-1); // free split here
}


static int		exec_command(char *word, char **words, char *buff, char ***env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char *command;

	command = NULL;
	if (check_builtin(word, words, buff, env) == 0)
		return (0);
	set_path(word, &command, env);
	pid = fork();
	if (pid == 0)
	{
		if (execve(command, words, *env) == -1)
		{
			ft_printf("%s: command not found\n", word);
			free(command);
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
	free(command); // enough?
	return (0);
}

static int		check_quote(char *buff)
{
	int i;
	int k;
	int c;

	c = 0;
	i = 0;
	k = 0;
	while (buff[i] != '\0')
	{
		if (c == 0 && (buff[i] == 39 || buff[i] == '"'))
			c = buff[i];
		if (buff[i] == c)
			k++;
		i++;
	}
	if ((k > 0 && k % 2 != 0))
	{
		ft_putstr("Error: problem with the quotes. Try again.\n");
		return (-1);
	}
	return (0);
}

int				ft_analyse_input(char *buff, char ***env)
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
	exec_command(words[0], words, buff, env);
	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words[i]);
	free(words);
	return (0);
}
