/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_str_utilities.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 16:33:10 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/12 16:44:14 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd(char *str, char *cmd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd_len != (int)ft_strlen(str))
		return (false);
	if (ft_strncmp(str, cmd, cmd_len) != 0)
		return (false);
	return (true);
}
