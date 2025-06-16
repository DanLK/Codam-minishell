/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:07:39 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/16 15:09:12 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	not_found_error(char *argv)
{
	char	*cmd;
	char	*error;
	char	*err_cmp;

	cmd = ft_strdup(argv);
	error = ft_strjoin("Minishell: ", cmd);
	err_cmp = ft_strjoin(error, " command not found");
	if (!err_cmp)
		perror("Error:");
	ft_putendl_fd(err_cmp, STDERR_FILENO);
	free(cmd);
	free(error);
	free(err_cmp);
}

void	permission_error(char *path)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(" Permission denied", STDERR_FILENO);
}
