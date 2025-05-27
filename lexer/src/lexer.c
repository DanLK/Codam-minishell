/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 16:50:37 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list	*scan(char *src)
{
	t_token_list	*tokens;
	t_scanner		*scanner;

	if (!src)
		return (NULL);
	if (!closed_quotes(src))
	{
		ft_printf("Minishell: syntax error: unclosed quotes\n");
		// exit(EXIT_FAILURE);
		// Must clear everything
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
		// ft_printf("[populate_tkns] current char: \"%c\"\n", src[s->cur]);
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
	c = get_current_char(&s->cur, src);
	if (c == '|')
		append_token(tokens, TKN_PIPE, "|");
	else if (c == '(')
		append_token(tokens, TKN_L_PAREN, "(");
	else if (c == ')')
		append_token(tokens, TKN_R_PAREN, ")");
	else if (c == '=')
		append_token(tokens, TKN_EQUAL, "=");
	else if (c == '>' || c == '<')
		redir_tkn(tokens, src, s, c);
	else if (c == '$' || c == '"' || c == '\'')
		tkn_quote(tokens, src, s, c);
	else if (c == '-' || ft_isalnum(c) || issymbol(c) || c == ':')
		tkn_opt_word(tokens, src, s, c);
}
