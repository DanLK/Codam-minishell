/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:06:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/21 16:21:52 by rojornod         ###   ########.fr       */
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
	else if (signal == SIGQUIT)
	{
		g_received = SIGQUIT;
	}
}
static void heredoc_handler(int signal)
{
    if (signal == SIGINT)
    {
		g_received = SIGINT;
		rl_done = 1;
		//write(1,"test\n", 5);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
    }
	else if (signal == SIGQUIT)
	{
		g_received = SIGQUIT;
		// write(1, "sigquit\n", 8);
	}
}

// I need to create a signal handler function for each of parent, child and heredoc
void	signal_action(void)
{
	struct sigaction	action;

	write(1, "signal_action called\n", 21);
	action.sa_flags = 0;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

int	heredoc_action(void)
{
	struct sigaction	action;
	
	ft_printf("heredoc_action called\n");
	//memset(&action, 0, sizeof(struct sigaction));
	action.sa_flags = SA_RESETHAND;
	action.sa_handler = heredoc_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	return (0);
}

//returns the caught signal
int	get_signal_received(void)
{
	return g_received;
}

// sets the global variable to 0, resets from the catched signals
// if its 0 it lets you implement your own
void reset_signal(void)
{
	ft_printf("[signal was: %d ", g_received);
    g_received = 0;
	ft_printf("and was set to: %d]\n", g_received);
}
