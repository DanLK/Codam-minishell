/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:06:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/20 16:28:05 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/******************************************************************************

	This is the handling of signals
	ctrl + C - sends SIGINT signal which interrupts the current process
	ctrl + D - is not a signal, its an End of File indicator, exits the shell
	ctrl + \ - sends SIGQUIT, does nothing
	
*****************************************************************************/

void	signal_reciever(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("^C\n");
		exit(130);
	}
	else if (signal == SIGQUIT)
		ft_printf("nothing happens");
	/* 
		ctrl + D does not send a signal but instead causes input functions
	to return EOF
		I don't think this if condition works but I'll leave it for now 
	and change it later
	*/
	if (!signal)
	{
		ft_printf("exit\n");
		exit(0);
	}
}

void	signal_handler(int signal)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = signal_reciever;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}
