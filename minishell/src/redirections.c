/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 10:53:23 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/19 11:26:30 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_redir_out(char *file)
{
	int		fd;
	char	*error;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (errno == 13)
	{
		error = error_mssg(file, ": Permission denied\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		error = error_mssg(file, ": No such file or directory\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		close(fd);
	close(fd);
	return (0);
}

int	exec_redir_append(char *file)
{
	int		fd;
	char	*error;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (errno == 13)
	{
		error = error_mssg(file, ": Permission denied\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		error = error_mssg(file, ": No such file or directory\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		close(fd);
	close(fd);
	return (0);
}

int	exec_redir_in(char *file)
{
	int		fd;
	char	*error;

	fd = open(file, O_RDONLY);
	if (errno == 13)
	{
		error = error_mssg(file, " : Permission denied\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		error = error_mssg(file, ": No such file or directory\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		close(fd);
	close (fd);
	return (0);
}
