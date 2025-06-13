/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/13 16:09:05 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list	*scan(char *src)
{
	t_token_list	*tokens;
	t_scanner		*scanner;

	if (!src)
		return (NULL);
	if (!closed_quotes(src, false, false))
	{
		ft_putendl_fd("Minishell: syntax error: unclosed quotes", STDERR_FILENO);
		return (NULL);
	}
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
		get_cur_token(tokens, src, s);
	}
	append_token(tokens, TKN_END, "END");
	return (tokens);
}

void	get_cur_token(t_token_list *tokens, char *src, t_scanner *s)
{
	char	c;

	if (!tokens || !src)
		return ;
	consume_space(s, src);
	c = get_cur_char(&s->cur, src);
	if (c == '|')
		append_token(tokens, TKN_PIPE, "|");
	else if (c == '>' || c == '<')
		redir_tkn(tokens, src, s, c);
	else if ((ft_isalpha(c) || c == '_') && is_assignment(s, src))
		tkn_assignment(tokens, s, src);
	else if (ft_isalnum(c) || issymbol(c))
		tkn_opt_word(tokens, src, s, c);
}
//Symbols that we may not want to read: ` 

