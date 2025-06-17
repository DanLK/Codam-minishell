/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/17 15:46:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 15:48:17 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(t_token_list *tokens, t_vars **head)
{
	t_token_node	*node;
	int				exit_status;

	if (!tokens || !head)
		return (1);
	node = tokens->head->next;
	exit_status = 0;
	if (!node)
		return (0);
	while (node)
	{
		exit_status = unset_builtin(head, node->token->lexeme);
		node = node->next;
	}
	return (exit_status);
}

static void	loop_export(t_token_node *node, t_vars *vars, int *exit_code)
{
	char			*var_name;
	char			*var_value;

	while (node)
	{
		var_name = node->token->lexeme;
		var_value = NULL;
		if (node->next && node->next->token->type == TKN_EQUAL)
		{
			if (node->next->next)
			{
				var_value = node->next->next->token->lexeme;
				node = node->next->next->next;
			}
			else
			{
				var_value = "";
				node = node->next->next;
			}
		}
		else
			node = node->next;
		*exit_code = export_builtin(&vars, var_name, var_value);
	}
}

int	execute_export(t_token_list *tokens, t_vars *vars)
{
	int				exit_code;
	t_token_node	*node;

	if (!tokens || !vars)
		return (1);
	if (!tokens->head->next)
	{
		export_builtin(&vars, NULL, NULL);
		return (0);
	}
	node = tokens->head->next;
	exit_code = 0;
	loop_export(node, vars, &exit_code);
	return (exit_code);
}

int	execute_ext_command(t_t_node **root, t_vars *vars, t_info *info)
{
	int				size;
	char			**command;
	t_token_list	*tokens;
	int				exit_code;

	if (!root || !vars || !info)
		return (1);
	exit_code = 0;
	tokens = (*root)->tokens;
	size = len_token_list(tokens);
	command = tkn_list_to_array(tokens);
	if (!command)
		return (1);
	exit_code = exec_external_com(vars, command, size, info);
	clear_array(command);
	return (exit_code);
}
