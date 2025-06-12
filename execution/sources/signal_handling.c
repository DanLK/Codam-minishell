/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/20 10:06:02 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/12 16:42:27 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

volatile sig_atomic_t	g_received = 0;

/******************************************************************************

		This is the handling of signals
		ctrl + C - sends SIGINT signal which interrupts the current process
		ctrl + D - not a signal, its an End of File indicator, exits the shell
		ctrl + \ - sends SIGQUIT, does nothing
		ioctl function basically fakes an enter press by the user 
	(by way of the TIOCSTI command which injects input into the 
	terminals input buffer, emulaing presses as if they were typed by the user) 
	this way readline doesnt ignore the first input by a user after a ctrl-c
	
******************************************************************************/
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		char line;

		line = '\n';
		g_received = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, &line);
	}
}

void	child_proc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_received = SIGINT;
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
