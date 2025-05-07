/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:19:52 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/02 14:33:56 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_external_cmd(t_vars	*head, char *command)
{

	if (!find_path(head, command))
	{
		debug_print("command is not external", 'r');
		return (1);
	}
	else
	{
		debug_print("command is external", 'r');
		return (0);
	}
}

int	is_builtin(char *command)
{
	int		i;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], command) == 0)
		{
			debug_print("command is a builtin", 'r');
			return (1);
		}
		i++;
	}
	debug_print("command is not a builtin", 'r');
	return (0);
}

int	find_cmd(t_vars *head, char *cmd)
{
	int		i;
	char	*built[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (built[i])
	{
		if (ft_strcmp(built[i], cmd) == 0)
		{
			debug_print("command is a builtin", 'r');
			return (1);
		}
		i++;
	}
	debug_print("command is not a builtin", 'r');
	if (!find_path(head, cmd))
	{
		debug_print("command is not external", 'r');
		return (1);
	}
	else
	{
		debug_print("command is external", 'r');
		return (0);
	}
}
