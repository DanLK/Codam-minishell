/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 11:16:24 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/12 16:45:56 by dloustal      ########   odam.nl         */
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
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute_src(root, head, info);
	close(fd[1]);
	return (0);
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
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_src(root, head, info);
	return (0);
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

	if (pipe(fd) < 0)
		return (1);
	pid_left = fork();
	if (pid_left < 0)
		return (1);
	if (pid_left == 0)
	{
		pipe_l(fd, &(*root)->left, head, info);
		exit(EXIT_SUCCESS);
	}
	pid_right = fork();
	if (pid_right < 0)
		return (1);
	if (pid_right == 0)
	{
		pipe_r(fd, &(*root)->right, head, info);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_l, 0);
	waitpid(pid_right, &status_r, 0);
	return (WEXITSTATUS(status_r));
}
