/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/18 11:16:24 by rojornod      #+#    #+#                 */
/*   Updated: 2025/05/29 12:15:51 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/******************************************************************************
*
*	- Helper function that specifies what will be done in the left child
*  	- Closes unused fd[0] for reading	
*	- Duplicates the writing fd (fd[1]) then closes that pipe
*	- Recursively calls execute pipe again
*	
*******************************************************************************/
static int	pipe_l(int fd[2], t_t_node **root, t_vars *head, t_shell_info *info)
{
	
	close(fd[0]);
	// ft_printf("[pipe_l] Inside left pipe child\n");
	debug_print("inside left pipe child process", 'r');
	dup2(fd[1], STDOUT_FILENO);
	// ft_printf("pipe_l STDOUT fd: %d\n", STDOUT_FILENO);
	debug_print("after dup2", 'r');
	// ft_printf("[pipe_l] To execute: %s\n", (*root)->tokens->head->token->lexeme);
	execute_src(root, head, info);
	debug_print("executed command", 'r');
	close(fd[1]);
	debug_print("fd[1] closed", 'r');
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
static int	pipe_r(int fd[2], t_t_node **root, t_vars *head, t_shell_info *info)
{
	close(fd[1]);
	// ft_printf("[pipe_r] Inside right pipe child\n");
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_src(root, head, info);
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
int	execute_pipe(t_t_node **root, t_vars *head, t_shell_info *info)
{
	int		fd[2];
    pid_t	pid_left;
	pid_t	pid_right;
	int		status_l;
	int		status_r;

	// ft_printf("[execute_pipe] Opening pipe\n");
	if (pipe(fd) < 0)
		print_error('p');
	pid_left = fork();
	if (pid_left < 0)
		print_error('f');
	if (pid_left == 0)
	{
		pipe_l(fd, &(*root)->left, head, info);
		exit(EXIT_SUCCESS);
	}
	pid_right = fork();
	if (pid_right < 0)
		print_error('f');
	if (pid_right == 0)
	{
		pipe_r(fd, &(*root)->right, head, info);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_l, 0);
	waitpid(pid_right, &status_r, 0);
	// ft_printf("STDOUT fd: %d\n", STDOUT_FILENO);
	// ft_printf("STDIN fd: %d\n", STDIN_FILENO);
	return (0); // Maybe WEXITSTATUS(status_r)
}
