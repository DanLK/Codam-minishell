/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:05:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/17 10:55:16 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_cleanup(int fd)
{
	close(fd);
	reset_signal();
	rl_on_new_line();
	rl_replace_line("", 0);
	signal_action();
	rl_done = 1;
	rl_catch_signals = 0;
	rl_event_hook = NULL;
}

int	sim_press_hook(void)
{
	if (get_signal_received() == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

/******************************************************************************
*
* 		Helper function for when the delimiter is reached.
*		We reopen the file but in readonly mode and get next line will be 
*	called until it returns null and every line will be printed to the 
*	standard output
*	unlink will delete the file after it's not in use anymore
*	
******************************************************************************/
int	delim_found(int fd, char *read_input)
{
	close(fd);
	if (!read_input)
		ft_printf("warning: recieved end of file\n");
	fd = open(".temp_heredoc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".temp_heredoc");
	reset_signal();
	signal_action();
	return (0);
}

void	init_heredoc(void)
{
	rl_event_hook = sim_press_hook;
	reset_signal();
}
