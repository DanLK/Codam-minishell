/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:14:24 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/16 10:54:58 by rojornod         ###   ########.fr       */
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

	i = 0;
	current = head;
	current = find_vars(head, "PATH");
	temp_path = ft_split(current->value, ':'); //malloc freed after a valid path is found or not
	while (temp_path[i])
	{
		temp_path[i] = ft_strjoin(temp_path[i], "/"); //malloc freed after a valid path is found or not
		temp_path[i] = ft_strjoin(temp_path[i], command); //malloc freed after a valid path is found or not
		if (access(temp_path[i], F_OK) == 0)
		{
			path = ft_strdup(temp_path[i]); //malloc freed in the create_child_proc function
			free_array(temp_path);
			return (path);
		}
		i++;
	}
	ft_printf("\n");
	free_array(temp_path);
	return (ft_printf("bash: %s: command not found\n", command), NULL);
}

void	exec_external_com(t_vars *head, char **envp, char **command, int size)
{
	char	*path;

	path = find_path(head, command[0]);
	create_child_proc(head, command, path, size);
}
