/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_var_assignment.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/17 15:47:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 15:48:33 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(t_token_node **node, char *var_value)
{
	if ((*node)->next->token->type == TKN_EQUAL)
	{
		if ((*node)->next->next
			&& (*node)->next->next->token->type == TKN_VAR_VALUE)
		{
			var_value = (*node)->next->next->token->lexeme;
			if ((*node)->next->next->next)
				(*node) = (*node)->next->next->next;
			else
				(*node) = (*node)->next;
		}
		else
		{
			var_value = "";
			(*node) = (*node)->next->next;
		}
		return (var_value);
	}
	else
		return (NULL);
}

int	execute_assignment(t_token_list *tokens, t_vars *vars)
{
	char			*var_name;
	char			*var_value;
	t_token_node	*node;
	t_vars			*temp;

	var_value = NULL;
	if (!tokens || !vars)
		return (1);
	node = tokens->head;
	while (node->token->type == TKN_VAR_NAME)
	{
		var_name = node->token->lexeme;
		var_value = get_var_value(&node, var_value);
		if (!var_value)
			return (1);
		temp = find_vars(vars, var_name);
		if (temp)
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_strdup(var_value);
		}
		else
			add_var(&vars, var_name, var_value, 0);
	}
	return (0);
}
