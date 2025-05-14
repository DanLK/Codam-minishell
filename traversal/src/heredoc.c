/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:05:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/14 17:34:13 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int heredoc(t_vars *vars, t_shell_info *info, char *delim)
{
	(void)vars;
	(void)info;
	(void)delim;
	int		fd;
	
	fd = open(".temp_heredoc", O_WRONLY | O_APPEND | O_CREAT, 0644);

	return (0);
}