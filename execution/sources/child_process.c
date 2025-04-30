/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:31 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/30 13:43:28 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_child_proc(t_vars *vars, char **cmd, char *path, int size)
{
	//t_fd_info	*info;
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
		ft_printf("**%s**%d**\n", argv[i], i);
		i++;
	}
	argv[i] = NULL;
	pid = fork();
	debug_print("forking program", 'r');
	if (pid == 0) //if pid = 0 then we are in child process
	{
		debug_print("inside child process", 'r');
		execve(path, argv, env_copy);
		debug_print("exiting child process", 'r');
		exit(130);
	}
	else if (pid > 0) //if pid is bigger than 0 we are in the parent process
	{ 
		int	w_status;
		
		while (waitpid(-1, &w_status, 0) > 1);
		if (WIFEXITED(w_status))
			ft_printf("Child process exited with status: %d\n", WEXITSTATUS(w_status));
	}
	else //if less than 0 something went wrong
	{
		// ft_printf("Error creating child process\n");
		return (1);	
	}
	free(path);
	free_array(argv);
	return (EXIT_SUCCESS);
}

