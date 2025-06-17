/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msgs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/16 15:07:39 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/17 12:17:33 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	not_found_error(char *argv)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd(" command not found", STDERR_FILENO);
}

void	permission_error(char *path)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(" Permission denied", STDERR_FILENO);
}

void	is_directory_error(char *path)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(" Is a directory", STDERR_FILENO);
}

void	no_such_file_error(char *argv)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd(" No such file or directory", STDERR_FILENO);
}