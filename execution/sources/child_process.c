/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:31 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/02 17:44:50 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	child_process(char *path, char	**argv, char **env_copy,t_shell_info	*info)
{
	info->is_child_running++;
	execve(path, argv, env_copy);
	perror("execve error");
	return (126);
}

static void parent_process(t_shell_info	*info)
{
	int				w_status;

	while (waitpid(-1, &w_status, 0) > 1);
	if (WIFEXITED(w_status))
	{	info->is_child_running--;
		ft_printf("Child process exited with statussss: %d\n", WEXITSTATUS(w_status));
	
	}
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
	while (cmd[i]) 
	{
		argv[i] = ft_strdup(cmd[i]); //malloc used needs to be free
		if (!argv[i])
			return (free_array(argv), EXIT_FAILURE);
		i++;
	}
	argv[i] = NULL;
	pid = fork();
	if (pid == 0) //if pid = 0 then we are in child process
		child_process(path, argv, env_copy, info);
	else if (pid > 0) //if pid is bigger than 0 we are in the parent process
		parent_process(info);
	else //if less than 0 something went wrong
		return (1);	
	return (free(path), free_array(argv), EXIT_SUCCESS);
}
