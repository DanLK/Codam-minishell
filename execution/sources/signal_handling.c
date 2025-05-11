/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:06:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/08 17:20:34 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_recieved = 0;
/******************************************************************************

	This is the handling of signals
	ctrl + C - sends SIGINT signal which interrupts the current process
	ctrl + D - is not a signal, its an End of File indicator, exits the shell
	ctrl + \ - sends SIGQUIT, does nothing
	
*****************************************************************************/

void	signal_handler(int signal)
{
	if (signal == SIGINT) 
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_recieved = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (!signal) //does nothing for now
	{
		ft_printf("exit\n");
		g_recieved = 1;
		exit(0);
	}
}

// I need to create a signal handler function for each of parent, child and heredoc
void	signal_action(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	child_signal_action(void)
{
	struct sigaction	child_action;
	
	child_action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &child_action, NULL);
	sigaction(SIGQUIT, &child_action, NULL);
}
