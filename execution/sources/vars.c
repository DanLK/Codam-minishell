/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:31:59 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/24 16:10:58 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*create_var(char *name, char *value, int exported)
{
	t_vars *new_node = malloc(sizeof(t_vars));
	if (!new_node)
	{
		perror("malloc on new node failed");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->exported = exported;
	new_node->next = NULL;
	return(new_node);
}

t_vars	*add_var(t_vars **head, char *name, char *value, int exported)
{
	t_vars	*new_node = create_var(name, value, exported);
	t_vars	*current;

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

void print_vars(t_vars *vars)
{
	while (vars != NULL)
	{
		printf("%s \n", vars->name);
		printf("%s \n", vars->value);
		printf("%d \n", vars->exported);
		vars = vars->next;
	}
}