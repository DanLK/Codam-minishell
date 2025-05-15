/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:05:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/15 17:08:05 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/traversal.h"

/******************************************************************************
*
* 		Helper function for when the delimiter is reached.
*		get next line will be called until it returns null and every line will be 
*	printed to the standard output
*	unlink will delete the file after it's not in use anymore
*	
******************************************************************************/
static int delim_found(int fd)
{
	char	*buf = NULL;
	
	ft_printf("[limiter found]\n");
	close(fd);
	fd = open(".temp_heredoc", O_RDONLY);
	while ((buf = get_next_line(fd)) != NULL)
	{
		ft_printf ("%s", buf);
		free(buf);
	}
	unlink(".temp_heredoc");
	return (0);
}

/******************************************************************************
*
* 	This will be the main heredoc function. Once a heredoc is detected this will
*	be called
*
******************************************************************************/
int heredoc(t_vars *vars, t_shell_info *info, char *delim)
{
	(void)vars;
	(void)info;
	(void)delim;
	int		fd;
	char 	*read_input;
	
	fd = open(".temp_heredoc", O_WRONLY | O_APPEND | O_CREAT, 0644);
	read_input = readline("heredoc> ");
	while (read_input)
	{
		if (ft_strcmp(read_input, delim) == 0)
		{
			delim_found(fd);
			return (0);
		}	
		write(fd, read_input, ft_strlen(read_input));
		write(fd,"\n",1);
		// free(read_input);
		read_input = readline("heredoc> ");
	}
	close(fd);
	
	return (0);
}

