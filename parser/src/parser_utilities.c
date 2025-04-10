/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utilities.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/10 13:05:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/10 13:17:28 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_operator(t_token_node *node)
{
	enum e_Type	 type; 
	if (!node)
		return (false);
	type = node->token->type;
	if (type < REDIR_IN || type > PIPE)
		return (false);
	return (true);
}
