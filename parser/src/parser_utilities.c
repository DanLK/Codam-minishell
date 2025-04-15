/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 13:05:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/15 15:48:58 by dloustal      ########   odam.nl         */
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
