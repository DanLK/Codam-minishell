/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:50:26 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/11 15:34:14 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_action(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

int	heredoc_action(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = heredoc_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	return (0);
}

int	child_proc_action(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = child_proc_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	return (0);
}
