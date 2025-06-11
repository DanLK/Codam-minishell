/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/11 17:11:56 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list	*scan(char *src)
{
	t_token_list	*tokens;
	t_scanner		*scanner;
	// bool			in_single;
	// bool			in_double;

	if (!src)
		return (NULL);
	// in_single = false;
	// in_double = false;
	if (!closed_quotes(src, false, false))
	{
		ft_printf("Minishell: syntax error: unclosed quotes\n");
		//Return NULL and then outside we can check whether the token list was NULL
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
	c = get_cur_char(&s->cur, src);
	if (c == '|')
		append_token(tokens, TKN_PIPE, "|");
	// else if (c == '(')
	// 	append_token(tokens, TKN_L_PAREN, "(");
	// else if (c == ')')
	// 	append_token(tokens, TKN_R_PAREN, ")");
	else if (c == '=')
		append_token(tokens, TKN_EQUAL, "=");
	else if (c == '>' || c == '<')
		redir_tkn(tokens, src, s, c);
	else if (c == '-' || ft_isalnum(c) || issymbol(c) || c == ':'
			|| c == '$' || c == '"' || c == '\'' || c == '('
			|| c == ')')
		tkn_opt_word(tokens, src, s, c);
	// else if (c == '$' && is_next(&(s->cur), src, '?'))
	// 	append_token(tokens, TKN_EXIT_STATUS, "$?");
	// else if (c == '"' || c == '\'') //(c == '$' && is_variable_tkn(src, s)
	// 	tkn_quote(tokens, src, s, c);
}
