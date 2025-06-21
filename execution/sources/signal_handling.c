/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:06:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/21 11:33:35 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

volatile sig_atomic_t	g_received = 0;

/******************************************************************************
*
*		ioctl(STDIN_FILENO, TIOCSTI, &line) - basically fakes an enter press by
*	the user (by way of the TIOCSTI command which injects input into the 
*	terminals input buffer, emulaing presses as if they were typed by the user) 
*	this way readline doesnt ignore the first input by a user after a ctrl-c
*		ioctl(STDIN_FILENO, TCFLSH, TCIFLUSH) - makes so that the first
*	keystroke by the user isn't ignored by readline by discarding any unread
*	bytes in the input queue.
*	
******************************************************************************/
void	signal_handler(int signal)
{
	char	line;

	if (signal == SIGINT)
	{
		line = '\n';
		g_received = SIGINT;
		ioctl(STDIN_FILENO, TCFLSH, TCIFLUSH);
		rl_done = 1;
		ioctl(STDIN_FILENO, TIOCSTI, &line);
	}
}

void	child_proc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_received = SIGINT;
		rl_done = 1;
	}
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
