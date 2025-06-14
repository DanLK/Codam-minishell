/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/14 15:07:20 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

t_vars	*initialize_data(void)
{
	t_vars	*head;

	head = malloc(sizeof(t_vars));
	if (!head)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	ft_memset(head, 0, sizeof(t_vars));
	return (head);
}

t_info	*initialize_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	ft_memset(info, 0, sizeof(t_info));
	info->fdin = dup(STDIN_FILENO);
	info->fdout = dup(STDOUT_FILENO);
	return (info);
}

char	*get_home_dir(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = NULL;
	if (!getcwd(buff, PATH_MAX + 1))
		return (NULL);
	current_directory = ft_strdup(buff);
	if (!current_directory)
		return (NULL);
	return (current_directory);
}

/******************************************************************************
*	
*	-This functon will copy all the environment variables given by the envp
*	 variable passed by the main();
*	-They are stored in the t_vars linked list;
*	-Changed the function to use strchr to the detect te first = 
*	then instead of using split, use substr to extract the name of the variable 
*	starting from 0 and up to the first equal. then use strdup to copy the rest 
*	of the string to value
*
******************************************************************************/
void	copy_env(t_vars **head, char **envp)
{
	int		i;
	char	*value;
	char	*name;
	char	*first_equal;
	
	(void)head;
	(void)value;
	i = 0;
	while (envp[i])
	{
		first_equal = ft_strchr(envp[i], '=' );
		name = ft_substr(envp[i], 0, first_equal - envp[i]);
		value = ft_strdup(first_equal + 1);
		if (!name || !value)
			exit(EXIT_FAILURE);
		else if (name && value)
		 	add_var(head, name, value, 1);
		free(name);
		free(value);
		i++;
	}
}
