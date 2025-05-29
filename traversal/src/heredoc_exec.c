/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 15:40:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/29 12:13:01 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 * This is really a redir in but with looking up the file
*******************************************************************************/
void	exec_heredoc(char *file)
{
	// int		cur_hd;
	int		fd;
	// char	*file;

	// cur_hd = info->cur_hd;
	// ft_putendl_fd(ft_itoa(info->cur_hd), info->fdout);
	// file = ft_strjoin(".tmp_heredoc", ft_itoa(info->cur_hd));
	// ft_printf("[exec_heredoc] opening file: %s\n", file);
	fd = open(file, O_RDONLY);
	// ft_putendl_fd(ft_itoa(info->cur_hd), info->fdout);
	// ft_printf("[exec_heredoc] before cur_hd = %d\n", info->cur_hd);
	// info->cur_hd++;
	// ft_putendl_fd(ft_itoa(info->cur_hd), info->fdout);
	// ft_printf("[exec_heredoc] after cur_hd = %d\n", info->cur_hd);
	// ft_printf("[exec_heredoc] fd is %d\n", fd);
	if (fd < 0)
	{
		ft_printf("[exec_heredoc] open failed -- file: %s\n", file);
		close(fd);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_printf("[exec_heredoc] dup failed\n");
		close(fd);
		return ;
	}
	// ft_printf("[exec_heredoc] success\n");
	close(fd);
	unlink(file); // Protect 
	// ft_putstr_fd("[exec_heredoc] Closed file...\n", info->fdout);
	// free(file);
}