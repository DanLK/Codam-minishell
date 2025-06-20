/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:14:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/20 12:15:24 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static char	*join_path(char **temp_p, int i, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(temp_p[i], "/");
	free(temp_p[i]);
	if (!temp)
		return (free_array(temp_p), NULL);
	temp_p[i] = temp;
	temp = ft_strjoin(temp_p[i], cmd);
	free(temp_p[i]);
	temp_p[i] = temp;
	if (!temp_p[i])
		return (free_array(temp_p), NULL);
	else
		return (temp_p[i]);
}

static char	*finding_path(char	**temp_p, char *path, char *cmd)
{
	int	i;

	i = 0;
	while (temp_p[i])
	{
		temp_p[i] = join_path(temp_p, i, cmd);
		if (access(temp_p[i], F_OK) == 0)
		{
			if (access(temp_p[i], X_OK) != 0)
			{
				path = ft_strdup(temp_p[i]);
				if (!path)
					return (free_array(temp_p), NULL);
			}
			else
			{
				path = ft_strdup(temp_p[i]);
				if (!path)
					return (free_array(temp_p), NULL);
				return (free_array(temp_p), path);
			}
		}
		i++;
	}
	return (path);
}

/******************************************************************************
*
*	- 	This function takes as arguments the environment list and the external
*	 command we are looking for.
	-	It will split the PATH variable so that we can loop through all the 
	 paths and find where the executable of that specific command is stored
	-	
******************************************************************************/
char	*find_path(t_vars *head, char *command)
{
	t_vars	*current;
	char	**temp_path;
	char	*path;

	path = NULL;
	current = head;
	current = find_vars(head, "PATH");
	if (!current)
		return (NULL);
	temp_path = ft_split(current->value, ':');
	if (!temp_path)
		return (NULL);
	path = finding_path(temp_path, path, command);
	if (!path)
		return (ft_printf(""), free_array(temp_path), NULL);
	else
		return (path);
}

int	exec_external_com(t_vars *head, char **cmd, int size, t_info *in)
{
	char	*path;
	int		exit_code;

	(void)in;
	exit_code = 0;
	if (ft_strchr(cmd[0], '/') != 0)
		exit_code = create_child_proc(head, cmd, ft_strdup(cmd[0]), size);
	else
	{
		path = find_path(head, cmd[0]);
		if (!path)
			return (not_found_error(cmd[0]), free(path), 127);
		exit_code = create_child_proc(head, cmd, path, size);
	}
	return (exit_code);
}
