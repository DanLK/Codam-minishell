/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msgs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 15:07:39 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/19 12:10:50 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*error_mssg(char *file, char *type)
{
	char	*err_0;
	char	*err_1;
	char	*final;

	err_0 = ft_strdup("Minishell: ");
	err_1 = ft_strjoin(err_0, file);
	final = ft_strjoin(err_1, type);
	free(err_0);
	free(err_1);
	return (final);
}

void	not_found_error(char *argv)
{
	char	*error;

	error = error_mssg(argv, " command not found\n");
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
}

void	permission_error(char *path)
{
	char	*error;

	error = error_mssg(path, " Permission denied\n");
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
}

void	is_directory_error(char *path)
{
	char	*error;

	error = error_mssg(path, " Is a directory\n");
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
}

void	no_such_file_error(char *argv)
{
	char	*error;

	error = error_mssg(argv, " No such file or directory\n");
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
}
