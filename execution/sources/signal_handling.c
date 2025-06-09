/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:06:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/09 13:03:39 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_received = 0;

/******************************************************************************

	This is the handling of signals
	ctrl + C - sends SIGINT signal which interrupts the current process
	ctrl + D - is not a signal, its an End of File indicator, exits the shell
	ctrl + \ - sends SIGQUIT, does nothing
	
******************************************************************************/
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_received = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_proc_handler(int signal)
{
	if (signal == SIGINT)
		g_received = SIGINT;
	if (signal == SIGQUIT)
		g_received = SIGQUIT;
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_received = SIGINT;
		rl_done = 1;
	}
}

//returns the caught signal
int	get_signal_received(void)
{
	return (g_received);
}

// sets the global variable to 0, resets from the catched signals
// if its 0 it lets you implement your own
void	reset_signal(void)
{
	g_received = 0;
}
