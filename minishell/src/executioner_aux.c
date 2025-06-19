/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner_aux.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/18 18:10:58 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/19 11:28:34 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redirection_aux(t_redir_node *cur, t_info *info, int *exit_code)
{
	while (cur)
	{
		*exit_code = call_redir(cur, info);
		if (*exit_code == 1)
			break ;
		cur = cur->next->next;
	}
}

t_token_node	*skip_empty_nodes(t_t_node **root)
{
	t_token_node	*node;

	node = (*root)->tokens->head;
	while (node && ft_strlen(node->token->lexeme) == 0)
	{
		if (!node->next)
			return (NULL);
		node = node->next;
		(*root)->tokens->head = node;
	}
	return (node);
}
