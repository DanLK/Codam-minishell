/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:31:59 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/16 15:30:56 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
		perror("malloc on new node failed");
		exit(EXIT_FAILURE);
	}
	if (!var_value)
	{
		new_node->name = ft_strdup(var_name); //malloc used here. needs to be free
		new_node->value = NULL;
		new_node->exported = 1;
		new_node->hidden = 1;
		new_node->next = NULL;
	}
	else
	{
		new_node->name = ft_strdup(var_name); //malloc used here. needs to be free
		new_node->value = ft_strdup(var_value); //malloc used here. needs to be free
		new_node->exported = exp;
		new_node->hidden = 0;
		new_node->next = NULL;
	}
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

	new_node = create_var(var_name, var_value, exp); //malloc is used here. needs to be free
	if (!(*head))
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	//ft_printf("variable added\n");
	return (*head);
}

/******************************************************************************
* 
*	-This function prints all the environment variables stored in t_vars list.
*	-Will be called by the env command.
*	-Can be used to see what is currently stored in all the variables.
*
*	EDGE CASES DONE :
*	-env won't print variables with no value attached to them
*
******************************************************************************/
void	env_builtin(t_vars *head)
{
	while (head)
	{
		if (head->name && head->hidden == 0)
			printf("%s=%s, export:[%d], hidden[%d] \n", head->name, head->value, head->exported, head->hidden);
		head = head->next;
	}
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
	size_t	size;
	t_vars	*current;
	char	*temp_var;

	size = ft_strlen(var_name);
	current = head;
	while (current)
	{
		if (ft_strncmp(current->name, var_name, size) == 0)
			//return (ft_printf("NAME[%s] VALUE [%s] HIDDEN [%d] EXPORT [%d]\n", current->name, current->value, current->hidden, current->exported), current);
			return (current);
			else
			current = current->next;
	}
	ft_printf("variable not found\n");
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
		head->value = ft_strdup(var_value); //malloc is used here. needs to be free
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
	debug_print("starting while loop");
	while (envp[i])
	{
		debug_print("splitting tokens");
		tokens = ft_split(envp[i], '=');
		debug_print("checking split successful");
		if (!tokens)
		{
			debug_print("error splitting tokens");
			exit(EXIT_FAILURE);
		}
		else if (tokens && tokens[0] && tokens[1]){
			add_var(head, tokens[0], tokens[1], 1);
			debug_print("var added");
		}
		free_array(tokens);
		i++;
		debug_print("loop finsihed");
	}
	debug_print("loop exited successfully");
	//free_array(tokens);
}
