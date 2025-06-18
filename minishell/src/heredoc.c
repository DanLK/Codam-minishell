/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 16:05:02 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/17 18:27:25 by dloustal      ########   odam.nl         */
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

void	init_sig_heredoc(void)
{
	rl_event_hook = sim_press_hook;
	reset_signal();
}
