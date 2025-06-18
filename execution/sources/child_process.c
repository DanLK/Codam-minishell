/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:31 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/18 16:35:58 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	check_if_directory(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == 0 && S_ISDIR(file_info.st_mode))
	{
		is_directory_error(path);
		return (126);
	}
}

int	child_process(char *path, char **argv, char **env_copy)
{
	child_proc_action();
	if (execve(path, argv, env_copy) == -1)
	{
		if (check_if_directory(path) == 126)
			exit(126);
		if (errno == 13)
		{
			permission_error(path);
			exit(126);
		}
		if ((*argv)[0] == '/' || (*argv)[0] == '.')
		{
			no_such_file_error(*argv);
			exit(127);
		}
		else
		{
			not_found_error(argv[0]);
			exit(127);
		}
	}
	exit(0);
}
/******************************************************************************
*	if (errno == EINTR) continue ; basically means if the error is 
*	EINTR (interrupted by signal)
*	the loop continues and call waitpid again. this prevents the parent form 
*	exiting early. in case a signal interruption happens in the child. 
*	if the error is something else the loop breaks
******************************************************************************/

static int	parent_process(char *path)
{
	int		w_status;
	pid_t	pid;

	pid = 0;
	free(path);
	w_status = 0;
	while (1)
	{
		pid = waitpid(-1, &w_status, 0);
		if (pid == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
	}
	if (WIFEXITED(w_status))
		return (signal_action(), WEXITSTATUS(w_status));
	if (WIFSIGNALED(w_status) && (WTERMSIG(w_status) == SIGQUIT))
		return (ft_printf("Quit (core dumped)\n", w_status),
			signal_action(), 131);
	if (WIFSIGNALED(w_status) && (WTERMSIG(w_status) == SIGINT))
		return (res_sig(), 130);
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

int	create_child_proc(t_vars *vars, char **cm, char *path, int siz)
{
	pid_t		pid;
	char		**argv;
	char		**env_copy;
	int			exit_code;

	exit_code = 0;
	env_copy = convert_env(vars);
	argv = malloc((siz + 1) * sizeof(char *));
	if (!argv)
		return (free_array(env_copy), EXIT_FAILURE);
	argv = copy_to_argv(cm, argv, env_copy, path);
	if (!argv)
		return (1);
	if (!path)
		return (free_array(env_copy), free_array(argv), EXIT_FAILURE);
	ignore_sig_action();
	pid = fork();
	if (pid == 0)
		exit_code = child_process(path, argv, env_copy);
	else if (pid > 0)
		exit_code = parent_process(path);
	else
		return (signal_action(), free_array(argv), free_array(env_copy),
			free(path), 1);
	return (signal_action(), free_array(env_copy), free_array(argv), exit_code);
}
