/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:31 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/18 17:40:57 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_child_proc(t_vars *vars, char **command, char *path, int size)
{
	//t_info	*info;
	pid_t	pid;
	char	**argv;
	char 	**env_copy;
	int 	i;
	
	i = 0;
	env_copy = convert_env(vars);
	argv = malloc((size + 1) * sizeof(char *));
	while (command[i])
	{
		argv[i] = ft_strdup(command[i]); //malloc used needs to be free
		i++;
	}
	argv[i] = NULL;
	pid = fork();
	debug_print("forking program", 'r');
	if (pid == 0) //if pid = 0 then we are in child process
	{
		debug_print("inside child process", 'r');
		//ft_printf("Parent PID: [%d]\nChild PID: [%d]\n", getppid(), getpid());
		execve(path, argv, env_copy);
		debug_print("exiting child process", 'r');
		exit(130);
	}
	else if (pid > 0) //if pid is bigger than 0 we are in the parent process
	{
		// ft_printf("Parent PID: [%d]\n", getpid());
		// ft_printf("Waiting for child to finish\n");
		waitpid(pid, NULL, 0);
		// ft_printf("child process finished\n");
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
