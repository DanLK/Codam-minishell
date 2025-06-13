/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 15:40:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/12 16:45:39 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
 * This is really a redir in but with looking up the file
 * If it fails to open
*******************************************************************************/
int	exec_heredoc(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			close(fd);
			return (1);
		}
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	unlink(file);
	return (0);
}
