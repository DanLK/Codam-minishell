/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 15:40:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 11:58:51 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 * This is really a redir in but with looking up the file
*******************************************************************************/
void	exec_heredoc(t_shell_info *info)
{
	// int		cur_hd;
	int		fd;
	char	*file;

	// cur_hd = info->cur_hd;
	file = ft_strjoin(".tmp_heredoc", ft_itoa(info->cur_hd));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("[exec_heredoc] open failed\n");
		info->cur_hd++;
		close(fd);
		return (free(file));
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_printf("[exec_heredoc] dup failed\n");
		info->cur_hd++;
		close(fd);
		return (free(file));
	}
	close(fd);
	unlink(file); // Protect 
	free(file);
	info->cur_hd++;
}