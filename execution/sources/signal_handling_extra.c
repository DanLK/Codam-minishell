/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling_extra.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 15:50:26 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/19 19:25:51 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	signal_action(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGPIPE, &action, NULL);
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
	action.sa_handler = SIG_DFL;
	sigemptyset(&action.sa_mask);
	sigaction(SIGPIPE, &action, NULL);
	return (0);
}

int	ignore_sig_action(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = SIG_IGN;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	return (0);
}

void	res_sig(void)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	signal_action();
}
