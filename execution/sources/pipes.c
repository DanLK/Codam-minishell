/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:16:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/30 15:47:32 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/******************************************************************************
*
*	-If a pipe is found in the full command this function will be called
*
*******************************************************************************/
// void	exec_pipe(t_vars *head, t_fd_info *info, char **envp, t_t_node *pipe_node)
// {
// 	pipe_node;
// 	(void)head;
// 	(void)envp;
// 	(void)info;
// 	int	pipes_nr;
// 	int	**pipes;
// 	int	cmd_nr;
// 	int	i;
// 	//pid_t	child_pid;
	
// 	pipes_nr = 0;
// 	cmd_nr = 0;
// 	debug_print("pipe recognized", 'r');
// 	if (!pipe_node)
// 		ft_printf("Command is null");
// 	while (pipe_node[cmd_nr])
// 	{
// 		ft_printf("Command [%d] [*%s*]\n", cmd_nr, pipe_node[cmd_nr]);
// 		cmd_nr++;
// 	}
// 	pipes_nr = cmd_nr -1;
// 	ft_printf("there are %d pipes\n there are %d commands\n", pipes_nr, cmd_nr);
// 	pipes = malloc(sizeof(int *) * pipes_nr); //malloc needs to be free
// 	i = 0;
// 	while (i < pipes_nr)
// 	{
// 		pipes[i] = malloc(sizeof(int) * 2); //malloc needs to be free
// 		ft_printf("trying to create a pipe [%d]\n", i);
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			perror("pipe error");
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			fork();
			
// 		}
// 			debug_print("pipe created", 'r');
// 		i++;
// 		ft_printf("i is %d\n", i);
// 	}
// }

//void	execute_pipe(t_t_node **root, t_vars *head)
//{
	// int		fd[2];
    // pid_t	pid_left;
	// pid_t	pid_right;

	// pipe(fd);
	// pid_left = fork();
	// if (pid_left < 0)
	// {
	// 	perror("fork failure");
	// 	exit(EXIT_FAILURE);
	// }
	// else if (pid_left > 0)
	// {
	// 	debug_print("inside pipe parent process", 'r');
	// }
	// else if (pid_left == 0)
	// {
		
	// 	debug_print("inside pipe child process", 'r');
	// 	close(fd[1]);
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	execute_pipe((*root)->left, head);
		
	// }
	
//}
