/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:40:53 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/04 12:12:53 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 * This is really a redir in but with looking up the file
 * If it fails to open
*******************************************************************************/
void	exec_heredoc(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return ;
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			close(fd);
			return ;
		}
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return ;
	}
	close(fd);
	unlink(file);
}
