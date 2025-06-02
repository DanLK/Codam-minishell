/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:14:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/02 15:25:13 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	current = head;
	current = find_vars(head, "PATH");
	if (!current)
		return (NULL);
	temp_path = ft_split(current->value, ':');
	if (!temp_path)
		return (NULL);
	while (temp_path[i])
	{
		temp = ft_strjoin(temp_path[i], "/");
		free(temp_path[i]);
		if (!temp)
			return (free_array(temp_path), NULL);
		temp_path[i] = temp;
		temp = ft_strjoin(temp_path[i], command);
		free(temp_path[i]);
		temp_path[i] = temp;
		if (!temp_path[i])
			return (free_array(temp_path), NULL);
		if (access(temp_path[i], F_OK) == 0)
		{
			path = ft_strdup(temp_path[i]);
			if (!path)
				return (free_array(temp_path), NULL);
			return (free_array(temp_path), path);
		}
		i++;
	}
	return (free_array(temp_path), NULL);
}

void	exec_external_com(t_vars *head, char **cmd, int size, t_shell_info *in)
{
	char	*path;

	(void)in;
	path = find_path(head, cmd[0]);
	if (!path)
	{
		create_child_proc(head, cmd, ft_strdup(cmd[0]), size);
	}
	else
	{
		create_child_proc(head, cmd, path, size);
	}
}
