/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:16:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/30 16:14:58 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/******************************************************************************
*
*	-If a pipe is found in the full command this function will be called
*
*******************************************************************************/
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
