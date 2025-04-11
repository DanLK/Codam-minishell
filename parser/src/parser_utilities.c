/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 13:05:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/11 13:40:53 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_operator(t_token_node *node)
{
	enum e_Type	 type; 
	if (!node)
		return (false);
	type = node->token->type;
	if (type < TKN_REDIR_IN || type >= TKN_PIPE)
		return (false);
	return (true);
}
