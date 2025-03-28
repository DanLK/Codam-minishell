/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:31:59 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/28 16:36:55 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*create_var(char *name, char *value)
{
	t_vars	*new_node;

	new_node = malloc(sizeof(t_vars));
	if (!new_node)
	{
		perror("malloc on new node failed");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

/*
	-before adding a variable I should check if that variable already exists
	-if it does, it should edit the value that variable has instead of
	 creating a new one witht the same name
*/
t_vars	*add_var(t_vars **head, char *var_name, char *var_value)
{
	t_vars	*new_node;
	t_vars	*current;
	
	new_node = create_var(var_name, var_value);
	if (!(*head))
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (*head);
}

void	print_vars(t_vars *vars)
{
	while (vars)
	{
		printf("%s=%s \n", vars->name, vars->value);
		vars = vars->next;
	}
}

t_vars	*find_vars(t_vars *head, char *var_name)
{
	size_t	size;
	t_vars	*current;

	size = ft_strlen(var_name);
	current = head;
	while (current)
	{
		if (ft_strncmp(current->name, var_name, size) == 0)
			return (current);
		else
			current = current->next;
	}
	return (NULL);
}

void	edit_var(t_vars *head, char *var_name, char *var_value)
{
	head = find_vars(head, var_name);
	if (!head)
		ft_printf("variable not found\n");
	else
	{
		free(head->value);
		head->value = ft_strdup(var_value);
	}
}

/******************************************************************************
*	
*	-This functon will copy all the environment variables given by the envp
*	 variable passed by the main();
*	-They are stored in the t_vars linked list;
*
******************************************************************************/
void	copy_env(t_vars **head, char **envp)
{
	int		i;
	char	**tokens;

	i = 0;
	while (envp[i])
	{
		tokens = ft_split(envp[i], '=');
		if (!tokens)
		{
			perror("error splitting tokens in the environment copy\n");
			exit(EXIT_FAILURE);
		}
		else if (tokens && tokens[0] && tokens[1])
			add_var(head, tokens[0], tokens[1]);
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
