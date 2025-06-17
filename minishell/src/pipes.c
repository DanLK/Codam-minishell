/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:16:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/17 16:13:50 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
*
*	- Helper function that specifies what will be done in the left child
*  	- Closes unused fd[0] for reading	
*	- Duplicates the writing fd (fd[1]) then closes that pipe
*	- Recursively calls execute pipe again
*	
*******************************************************************************/
static int	pipe_l(int fd[2], t_t_node **root, t_vars *head, t_info *info)
{
	int	exit_code;

	child_proc_action();
	exit_code = 0;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exit_code = execute_src(root, head, info);
	return (exit_code);
}

/******************************************************************************
*
*	- Helper function that specifies what will be done in the left child
*  	- Closes unused fd[1] for writing	
*	- Duplicates the reading fd (fd[0]) then closes that pipe
*	- Recursively calls execute pipe again
*	
*******************************************************************************/
static int	pipe_r(int fd[2], t_t_node **root, t_vars *head, t_info *info)
{
	int	exit_code;

	child_proc_action();
	exit_code = 0;
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exit_code = execute_src(root, head, info);
	return (exit_code);
}

/******************************************************************************
*
*	-If a pipe is found in the full command this function will be called
*
*******************************************************************************/
int	execute_pipe(t_t_node **root, t_vars *head, t_info *info)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_l;
	int		status_r;

	ignore_sig_action();
	if (pipe(fd) < 0)
		return (signal_action(), 1);
	pid_left = fork();
	if (pid_left < 0)
		return (signal_action(), 1);
	if (pid_left == 0)
	{
		status_l = pipe_l(fd, &(*root)->left, head, info);
		exit(status_l);
	}
	pid_right = fork();
	if (pid_right < 0)
		return (signal_action(), 1);
	if (pid_right == 0)
	{
		status_r = pipe_r(fd, &(*root)->right, head, info);
		exit(status_r);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_l, 0);
	waitpid(pid_right, &status_r, 0);
	return (signal_action(), WEXITSTATUS(status_r));
}
