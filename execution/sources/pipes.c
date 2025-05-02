/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:16:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/01 17:25:08 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/******************************************************************************
*
*	- Helper function that specifies what will be done in the left child
*  	- Closes unused fd[1] for writing	
*	- Duplicates the reading fd (fd[0]) then closes that pipe
*	- Recursively calls execute pipe again
*	
*******************************************************************************/
static int	pipe_r(int fd[2], t_t_node **root, t_vars *head)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_pipe(&(*root)->right, head);
	return (0);
}

/******************************************************************************
*
*	- Helper function that specifies what will be done in the left child
*  	- Closes unused fd[0] for reading	
*	- Duplicates the writing fd (fd[1]) then closes that pipe
*	- Recursively calls execute pipe again
*	
*******************************************************************************/
static int	pipe_l(int fd[2], t_t_node **root, t_vars *head)
{
	debug_print("inside left pipe child process", 'r');
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_pipe(&(*root)->left, head);
	return (0);
}

/******************************************************************************
*
*	- Helper function that prints an error message based on the char given
*	  p = pipe
*	  f = fork
*	- Returns 1 (EXIT FAILURE) after printing
*
*******************************************************************************/
static int	print_error(char type)
{
	if (type == 'p')
		perror("pipe error");
	else if (type == 'f')
		perror("fork error");
	return (EXIT_FAILURE);
}

/******************************************************************************
*
*	-If a pipe is found in the full command this function will be called
*
*******************************************************************************/
int	execute_pipe(t_t_node **root, t_vars *head)
{
	int		fd[2];
    pid_t	pid_left;
	pid_t	pid_right;
	int		w_status;

	if (pipe(fd) < 0)
		print_error('p');
	pid_left = fork();
	if (pid_left < 0)
		print_error('f');
	else if (pid_left == 0)
		pipe_l(fd, root, head);
	pid_right = fork();
	if (pid_right < 0)
		print_error('f');
	else if (pid_right == 0)
		pipe_r(fd, root, head);
	//parent process
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &w_status, 0);
	waitpid(pid_right, &w_status, 0);
}
