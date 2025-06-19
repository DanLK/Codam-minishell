/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 10:53:23 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/19 10:39:37 by dloustal      ########   odam.nl         */
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

int	exec_redir_append(char *file)
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

static char	*error_mssg(char *file, char *type)
{
	char	*err_0;
	char	*err_1;
	char 	*final;

	err_0 = ft_strdup("Minishell: ");
	err_1 = ft_strjoin(err_0, file);
	final = ft_strjoin(err_1, type);
	free(err_0);
	free(err_1);
	return (final);
}

int	exec_redir_in(char *file)
{
	int		fd;
	char	*error;

	fd = open(file, O_RDONLY);
	if (errno == 13)
	{
		// ft_putstr_fd("Minishell: ", STDERR_FILENO);
		// ft_putstr_fd(file, STDERR_FILENO);
		// ft_putendl_fd(": Permission denied", STDERR_FILENO);
		error = error_mssg(file, " : Permission denied\n");
		write(STDERR_FILENO, error, ft_strlen(error));
		free(error);
		restore_fd_after_fail(fd);
		return (1);
	}
	if (fd < 0)
	{
		// ft_putstr_fd("Minishell: ", STDERR_FILENO);
		// ft_putstr_fd(file, STDERR_FILENO);
		// ft_putendl_fd(": No such file or directory", STDERR_FILENO);
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
