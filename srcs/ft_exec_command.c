/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 19:34:03 by tcherret          #+#    #+#             */
/*   Updated: 2020/02/08 19:35:45 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		good_path_found(char ***tab, char **cmd, char **com, char *tmp)
{
	*cmd = tmp;
	free(*com);
	free_tab(tab);
	return (0);
}

static int		set_path(char *word, char **command, char ***env) // need to free ce path
{
	char *tmp;
	char *com;
	char *temp;
	char **split;
	int i;

	i = 0;
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
			return (good_path_found(&split, command, &com, temp));
		free(temp);
		i++;
	}
	free_tab(&split);
	free(com);
	return (-1); // free split here
}

static int		no_fork()
{
		ft_putstr("Error: fork did not work.\n");
		return (-1);
}

static int		wait_status(pid_t pid, char **command)
{
	pid_t	wpid;
	int		status;

	while (1)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			free(*command);
			return (0);
		}
	}
	return (0);
}

int				exec_command(char *word, char **words, char *buff, char ***env)
{
	pid_t	pid;
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
		}
	}
	else if (pid < 0)
		return (no_fork());
	return (wait_status(pid, &command));
}


