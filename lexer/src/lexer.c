/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/31 16:27:46 by dloustalot    ########   odam.nl         */
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
	append_token(tokens, END, "END");
	return (tokens);
}

void	get_cur_token(t_token_list *tokens, char *src, t_scanner *s)
{
	char	c;
	char	*lexeme;

	if (!tokens || !src)
		return ;
	consume_space(s, src);
	c = get_current_char(&s->cur, src);
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
		if (is_next(&(s->cur), src, '>'))
		{
			append_token(tokens, REDIR_OUT_APPEND, ">>");
			s->start += 2;
		}
		else
		{
			append_token(tokens, REDIR_OUT, ">");
			(s->start)++;
		}
		lexeme = read_filepath(s, src);
		append_token(tokens, FILE_PATH, lexeme);
		free(lexeme);
	}
	if (c == '<')
	{
		if (is_next(&(s->cur), src, '<'))
			append_token(tokens, HEREDOC, "<<");
		else
			append_token(tokens, REDIR_IN, "<");
	}
	if (c == '$')
	{
		if (is_next(&(s->cur), src, '?'))
			append_token(tokens, EXIT_STATUS, "$?");
		else
			append_token(tokens, ENV_VAR, "$");
	}
	if (c == '"')
	{
		lexeme = read_quoted(s, src, '"');
		append_token(tokens, DQ_STRING, lexeme);
		free(lexeme);
	}
	if (c == '\'')
	{
		lexeme = read_quoted(s, src, '\'');
		append_token(tokens, SQ_STRING, lexeme);
		free(lexeme);
	}
	if (c == '-')
	{
		if (is_next(&(s->cur), src, 'n'))
			append_token(tokens, OPTION_N, "-n");
		else
			perror("Invalid option: only -n is allowed.");
	}
	if (ft_isalnum(c) || issymbol(c))
	{
		lexeme = read_identifier(s, src);
		if (is_keyword(lexeme) != -1)
			append_token(tokens, is_keyword(lexeme), lexeme);
		else
			append_token(tokens, IDENTIFIER, lexeme);
		free(lexeme);
	}
}

