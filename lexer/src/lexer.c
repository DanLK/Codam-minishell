/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/24 14:57:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token_list	*scan(char *src)
{
	t_token_list	*tokens;

	if (!src)
		return (NULL);
	tokens = init_token_list();
	if (!tokens)
		return (NULL);
	tokens = populate_tokens(tokens, src);
	return (tokens);
}

t_token_list	*populate_tokens(t_token_list *tokens, char *src)
{
	int	current;
	int	start;

	if (!tokens || !src)
		return (NULL);
	current = 0;
	while (src[current])
	{
		start = current;
		get_cur_token(tokens, src, start, &current);
	}
	append_token(tokens, EOF, "EOF");
	return (tokens);
}

void	get_cur_token(t_token_list *tokens, char *src, int s, int *cur)
{
	char	c;
	char	*lexeme;

	if (!tokens || !src)
		return ;
	consume_space(cur, &s, src);
	c = get_current_char(cur, src);
	lexeme = "";
	if (c == '|')
		append_token(tokens, PIPE, "|");
	else if (c == '(')
		append_token(tokens, LEFT_PAREN, "(");
	else if (c == ')')
		append_token(tokens, RIGHT_PAREN, ")");
	else if (c == '=')
		append_token(tokens, EQUAL, "=");
	if (c == '>')
	{
		if (is_next(cur, src, '>'))
		{
			append_token(tokens, REDIR_OUT_APPEND, ">>");
			s += 2;
		}
		else
		{
			append_token(tokens, REDIR_OUT, ">");
			s++;
		}
		lexeme = read_filepath(cur, s, src);
		append_token(tokens, FILE_PATH, lexeme);
		free(lexeme);
	}
	if (c == '<')
	{
		if (is_next(cur, src, '<'))
			append_token(tokens, HEREDOC, "<<");
		else
			append_token(tokens, REDIR_IN, "<");
	}
	if (c == '$')
	{
		if (is_next(cur, src, '?'))
			append_token(tokens, EXIT_STATUS, "$?");
		else
			append_token(tokens, ENV_VAR, "$");
	}
	if (c == '"')
	{
		lexeme = read_quoted(cur, s, src, '"');
		append_token(tokens, DQ_STRING, lexeme);
		free(lexeme);
	}
	if (c == '\'')
	{
		lexeme = read_quoted(cur, s, src, '\'');
		append_token(tokens, SQ_STRING, lexeme);
		free(lexeme);
	}
	if (ft_isalnum(c) || c == '_')
	{
		lexeme = read_identifier(cur, s, src);
		if (is_keyword(lexeme) != -1)
			append_token(tokens, is_keyword(lexeme), lexeme);
		else
			append_token(tokens, IDENTIFIER, lexeme);
		free(lexeme);
	}
}

// void	get_redir_tkn(t_token_list *tokens, char *src, int s, int *cur)
// {

// }
