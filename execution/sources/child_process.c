/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:31 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/29 17:03:42 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	child_process(char *path, char **argv, char **env_copy, t_shell_info *info)
{
	(void)info;
	if (execve(path, argv, env_copy) == -1)
	{
		// perror("execve error");
		ft_printf("Minishell: %s command not found\n", argv[0]);
		// SHOULD CLEAN EVERYTHING
	}
	free(path);
	free_array(env_copy);
	free_array(argv);
	exit(126);
}

static void parent_process(t_shell_info	*info)
{
	int	w_status;

	w_status = 0;
	(void)info;
	while (waitpid(-1, &w_status, 0) > 0);
	if (WIFSIGNALED(w_status) && (WTERMSIG(w_status) == SIGQUIT))
		ft_printf("Quit (core dumped)\n", w_status);
	// if (WIFEXITED(w_status))
	// 	ft_printf("Child process exited with status: %d\n", WEXITSTATUS(w_status));
}

int	create_child_proc(t_vars *vars, char **cmd, char *path, int size, t_shell_info	*info)
{
	pid_t		pid;
	char		**argv;
	char 		**env_copy;
	int 		i;

	i = 0;
	env_copy = convert_env(vars);
	argv = malloc((size + 1) * sizeof(char *)); //malloc used here
	if (!argv)
		return (free_array(env_copy), EXIT_FAILURE);
	while (cmd[i]) 
	{
		argv[i] = ft_strdup(cmd[i]); //malloc used needs to be free
		if (!argv[i])
			return (free_array(argv), free_array(env_copy), free(path), EXIT_FAILURE);
		i++;
	}
	argv[i] = NULL;		
	if (!path)
		return (free_array(env_copy), free_array(argv), EXIT_FAILURE);
	pid = fork();
	if (pid == 0){ //if pid = 0 then we are in child process
		child_proc_action();
		child_process(path, argv, env_copy, info);}
	else if (pid > 0) //if pid is bigger than 0 we are in the parent process
		parent_process(info);
	else //if less than 0 something went wrong
		return (1);	
	return (free_array(env_copy), free_array(argv), EXIT_SUCCESS);
}
