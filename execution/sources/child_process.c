/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 11:11:31 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/11 12:17:17 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_process(char *path, char **argv, char **env_copy)
{
	child_proc_action();
	if (execve(path, argv, env_copy) == -1)
	{
		if (errno == 13)
		{
			ft_printf("%s: Permission denied\n", path);
			exit(126);
		}
		else
			ft_printf("Minishell: %s command not found\n", argv[0]);
	}
	exit(127);
}

static int	parent_process(char *path)
{
	int	w_status;

	free(path);
	w_status = 0;
	while
		(waitpid(-1, &w_status, 0) > 0);
	if (WIFEXITED(w_status))
		return (WEXITSTATUS(w_status));
	if (WIFSIGNALED(w_status) && (WTERMSIG(w_status) == SIGQUIT))
		return (ft_printf("Quit (core dumped)\n", w_status), 131);
	if (WIFSIGNALED(w_status) && (WTERMSIG(w_status) == SIGINT))
		return (130);
	return (1);
}

static char	**copy_to_argv(char **cmd, char **argv, char **env_copy,
				char *path)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		argv[i] = ft_strdup(cmd[i]);
		if (!argv[i])
			return (free_array(argv), free_array(env_copy), free(path), NULL);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	create_child_proc(t_vars *vars, char **cmd, char *path, int size)
{
	pid_t		pid;
	char		**argv;
	char		**env_copy;
	// int			i;
	int			exit_code;

	exit_code = 0;
	// i = 0;
	env_copy = convert_env(vars);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		return (free_array(env_copy), EXIT_FAILURE);
	argv = copy_to_argv(cmd, argv, env_copy, path);
	if (!argv)
		return (1);
	if (!path)
		return (free_array(env_copy), free_array(argv), EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		child_process(path, argv, env_copy);
	else if (pid > 0)
		exit_code = parent_process(path);
	else
		return (free_array(argv), free_array(env_copy), free(path), 1);
	return (free_array(env_copy), free_array(argv), exit_code);
}
