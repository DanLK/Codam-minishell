/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_process.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/16 11:11:31 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/13 18:02:58 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static void not_found_error(char *argv)
{
	char	*cmd;
	char	*error;
	char	*err_cmp;

	cmd = ft_strdup(argv);
	error = ft_strjoin("Minishell: ", cmd);
	err_cmp = ft_strjoin(error, " command not found");
	if (!err_cmp)
		perror("Error:");
	ft_putendl_fd(err_cmp, STDERR_FILENO);
	free(cmd);
	free(error);
	free(err_cmp);
}

int	child_process(char *path, char **argv, char **env_copy)
{
	struct stat sb;
	
	child_proc_action();
	if (execve(path, argv, env_copy) == -1)
	{
		if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd(" Is a directory", STDERR_FILENO);
			exit(126);
		}
		if (errno == 13)
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd(" Permission denied", STDERR_FILENO);
			exit(126);
		}
		else
		{
			// ft_printf("Minishell: %s command not found\n", argv[0]);
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
	pid = fork();
	if (pid == 0)
		exit_code = child_process(path, argv, env_copy);
	else if (pid > 0)
		exit_code = parent_process(path);
	else
		return (free_array(argv), free_array(env_copy), free(path), 1);
	return (free_array(env_copy), free_array(argv), exit_code);
}
