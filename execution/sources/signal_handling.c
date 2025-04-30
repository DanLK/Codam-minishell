/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:06:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/23 15:47:51 by rojornod         ###   ########.fr       */
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
	
		/* 
		ctrl + D does not send a signal but instead causes input functions
	to return EOF
		I don't think this if condition works but I'll leave it for now 
	and change it later
	*/
	if (!signal)
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
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}
