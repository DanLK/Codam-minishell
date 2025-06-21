/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 13:05:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/21 09:48:36 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	advance(t_parser *parser)
{
	t_token_node	*tmp;

	if (!parser)
		return ;
	tmp = parser->current;
	parser->current = parser->current->next;
	parser->previous = tmp;
}

bool	is_operator(enum e_Type type)
{
	return (type >= TKN_REDIR_IN && type <= TKN_PIPE);
}

bool	is_redirection(enum e_Type type)
{
	return (type >= TKN_REDIR_IN && type <= TKN_REDIR_OUT_APP);
}

// bool	is_redir_twochar(enum e_Type type)
// {
// 	return (type == TKN_HEREDOC || type == TKN_REDIR_OUT_APP);
// }
bool	has_heredoc(t_t_node *node)
{
	t_redir_node	*redir_node;

	redir_node = (*node->redirs);
	while (redir_node)
	{
		if (redir_node->type == TKN_HEREDOC)
			return (true);
		if (redir_node->next)
			redir_node = redir_node->next->next;
		else
			redir_node = redir_node->next;
	}
	return (false);
}

bool	is_redir(t_parser *parser)
{
	t_token_node	*tmp;

	if (!parser)
		return (false);
	tmp = parser->current;
	while (tmp)
	{
		if (is_redirection(tmp->token->type))
			return (true);
		if (tmp->token->type == TKN_PIPE)
			return (false);
		tmp = tmp->next;
	}
	return (false);
}
