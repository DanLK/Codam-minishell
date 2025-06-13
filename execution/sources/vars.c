/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vars.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/24 15:31:59 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/12 16:42:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static t_vars	*has_value(t_vars *new_node, char *name, char *value, int exp)
{
	new_node->name = ft_strdup(name);
	if (!new_node->name)
		return (NULL);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (NULL);
	new_node->exported = exp;
	new_node->hidden = 0;
	new_node->next = NULL;
	return (new_node);
}

/******************************************************************************
*
*	-Takes var_name and var_value as parameters
*	-Allocates memory to the size of the t_vars list
*	-Creates a new node with var_name and var_value assigned to new_node->name
*	 and new_node->value respectively. new_node->next is assigned NULL.
*	-Returns the new node.
*
******************************************************************************/
t_vars	*create_var(char *var_name, char *var_value, int exp)
{
	t_vars	*new_node;

	new_node = malloc(sizeof(t_vars));
	if (!new_node)
		return (NULL);
	if (!var_value)
	{
		new_node->name = ft_strdup(var_name);
		if (!new_node->name)
			return (NULL);
		new_node->value = ft_strdup("");
		if (!new_node->value)
			return (NULL);
		new_node->exported = 1;
		new_node->hidden = 1;
		new_node->next = NULL;
	}
	else
		new_node = has_value(new_node, var_name, var_value, exp);
	return (new_node);
}

/******************************************************************************
*
* 	-This function takes a double pointer to t_vars, a variable name and value
*	-It takes the new node created in create_var and adds it at the end of the
*	 list (when current->next is NULL).
*	
*	TO DO notes:
*	-before adding a variable it should check if that variable already exists
*	-if it does, it should edit the value that variable has instead of
*	 creating a new one witht the same name
*
*******************************************************************************/
t_vars	*add_var(t_vars **head, char *var_name, char *var_value, int exp)
{
	t_vars	*new_node;
	t_vars	*current;

	new_node = create_var(var_name, var_value, exp);
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

/******************************************************************************
*
*	-This function takes as arguments a pointer to the head of the list and
*	 the variable name that we want to look for.
*	-While the current node is not NULL it compares current->name to var_name.
*	-If the loop finds a match it returns that node and the values of each elem.
*	-If it doesn't find a match it returns an error message and NULL.
*
******************************************************************************/
t_vars	*find_vars(t_vars *head, char *var_name)
{
	t_vars	*current;

	current = head;
	while (current)
	{
		if (current->name && ft_strcmp(current->name, var_name) == 0)
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
		return ;
	else
	{
		free(head->value);
		head->value = ft_strdup(var_value);
	}
}
