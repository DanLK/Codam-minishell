/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 13:05:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/14 17:25:04 by dloustal      ########   odam.nl         */
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

/**************************************************************************** 
 * WARN_ING: Currently not using this function!
****************************************************************************/
bool	is_operator(t_token_node *node)
{
	enum e_Type	 type; 
	if (!node)
		return (false);
	type = node->token->type;
	if (type < TKN_REDIR_IN || type > TKN_PIPE)
		return (false);
	return (true);
}
