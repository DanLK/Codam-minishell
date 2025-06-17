/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:53:23 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/17 17:17:22 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
*
*	If a redirect out is found in the full command this function will be called
*
*******************************************************************************/
// int	execute_redir_out(t_t_node **root, t_vars *head, t_info *info)
// {
//     pid_t	pid;
// 	int		w_status;
// 	int		fd;

// 	pid = fork();
// 	if (pid < 0)
// 		ft_printf("fork error");
// 	if (pid == 0)
// 	{
// 		fd = open((*root)->right->tokens->head->token->lexeme, 
//			O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		if (fd < 0)
// 		{
// 			ft_printf("open failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) < 0)
// 		{
// 			ft_printf("dup failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		execute_src(&(*root)->left, head, info);
// 		close(fd);
// 		exit(EXIT_SUCCESS);
// 	}
// 	waitpid(pid, &w_status, 0);
// 	if (WIFEXITED(w_status))
// 		ft_printf("Child exited successfully\n");
// 	return (0);
// }

static int	restore_fd_after_fail(int fd)
{
	fd = open("/dev/null", O_RDONLY);
	if (fd < 0)
	{
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	tmp_redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (errno == 13)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		close(fd);
	close(fd);
	return (0);
}

int	tmp_redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (errno == 13)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		close(fd);
	close(fd);
	return (0);
}

int	tmp_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (errno == 13)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		close(fd);
	close (fd);
	return (0);
}

// int	execute_redir_in(t_t_node **root, t_vars *head, t_info *info)
// {
//     pid_t	pid;
// 	int		w_status;
// 	int		fd;

// 	pid = fork();
// 	if (pid < 0)
// 		ft_printf("fork error");
// 	if (pid == 0)
// 	{
// 		fd = open((*root)->right->tokens->head->token->lexeme, O_RDONLY);
// 		if (fd < 0)
// 		{
// 			ft_printf("open failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(fd, STDIN_FILENO) < 0)
// 		{
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		execute_src(&(*root)->left, head, info);
// 		close(fd);
// 		exit(EXIT_SUCCESS);
// 	}
// 	waitpid(pid, &w_status, 0);
// 	if (WIFEXITED(w_status))
// 		ft_printf("Child exited successfully\n");
// 	return (0);
// }

// int	execute_redir_app(t_t_node **root, t_vars *head, t_info *info)
// {
// 	pid_t	pid;
// 	int		w_status;
// 	int		fd;

// 	pid = fork();
// 	if (pid < 0)
// 		ft_printf("fork error");
// 	if (pid == 0)
// 	{
// 		fd = open((*root)->right->tokens->head->token->lexeme,
//			O_APPEND | O_WRONLY | O_CREAT, 0644);
// 		if (fd < 0)
// 		{
// 			ft_printf("open failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		if(dup2(fd, STDOUT_FILENO) < 0)
// 		{
// 			ft_printf("dup failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		execute_src(&(*root)->left, head, info);
// 		close(fd);
// 		exit(EXIT_SUCCESS);
// 	}
// 	waitpid(pid, &w_status, 0);
// 	if (WIFEXITED(w_status))
// 		ft_printf("Child exited successfully\n");
// 	return (0);
// }
