/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/14 18:03:53 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token	**scan(char *source)
{
	t_token	*tokens;
	int		current;

	if (!source)
		return (NULL);
	tokens = (t_token **)malloc(sizeof(t_token **));
	if (!tokens)
		return (NULL);
	current = 0;
	while (source[current])
	{
		ft_printf("%c\n", source[current]);
		current++;
	}
	return (tokens);
}
