/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 13:05:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 17:18:37 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	advance(t_parser *parser)
{
	t_token_node *tmp;

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

bool	is_redir_twochar(enum e_Type type)
{
	return (type == TKN_HEREDOC || type == TKN_REDIR_OUT_APP);
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
		if (tmp->token->type == TKN_PIPE) // Not sure if this is incorrect, it is to process only up to a pipe
			return (false);
		tmp = tmp->next;
	}
	return (false);
}
