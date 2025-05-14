/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/14 10:36:03 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list	*scan(char *src)
{
	t_token_list	*tokens;
	t_scanner		*scanner;

	if (!src)
		return (NULL);
	tokens = init_token_list();
	scanner = init_scanner(0, 0);
	if (!tokens || !scanner)
		return (NULL);
	tokens = populate_tkns(tokens, src, scanner);
	free(scanner);
	return (tokens);
}

t_token_list	*populate_tkns(t_token_list *tokens, char *src, t_scanner *s)
{
	if (!tokens || !src)
		return (NULL);
	while (src[s->cur])
	{
		s->start = s->cur;
		// ft_printf("[populate_tkns] current char: \"%c\"\n", src[s->cur]);
		get_cur_token(tokens, src, s);
	}
	append_token(tokens, TKN_END, "END");
	return (tokens);
}
