/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:06:59 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/31 16:53:57 by dloustalot    ########   odam.nl         */
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

	if (!tokens || !src)
		return ;
	consume_space(s, src);
	c = get_current_char(&s->cur, src);
	if (c == '|')
		append_token(tokens, PIPE, "|");
	else if (c == '(')
		append_token(tokens, LEFT_PAREN, "(");
	else if (c == ')')
		append_token(tokens, RIGHT_PAREN, ")");
	else if (c == '=')
		append_token(tokens, EQUAL, "=");
	else if (c == '>' || c == '<')
		redir_tkn(tokens, src, s, c);
	else if (c == '$' || c == '"' || c == '\'')
		tkn_quote(tokens, src, s, c);
	else if (c == '-' || ft_isalnum(c) || issymbol(c))
		tkn_opt_word(tokens, src, s, c);
}

void	redir_tkn(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '>')
	{
		if (is_next(&(s->cur), src, '>'))
		{
			append_token(tkns, REDIR_OUT_APPEND, ">>");
			s->start += 2;
		}
		else
		{
			append_token(tkns, REDIR_OUT, ">");
			(s->start)++;
		}
		lexeme = read_filepath(s, src);
		append_token(tkns, FILE_PATH, lexeme);
		free(lexeme);
	}
	else if (c == '<')
	{
		if (is_next(&(s->cur), src, '<'))
			append_token(tkns, HEREDOC, "<<");
		else
			append_token(tkns, REDIR_IN, "<");
	}
}

void	tkn_quote(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '$')
	{
		if (is_next(&(s->cur), src, '?'))
			append_token(tkns, EXIT_STATUS, "$?");
		else
			append_token(tkns, ENV_VAR, "$");
	}
	else if (c == '"')
	{
		lexeme = read_quoted(s, src, '"');
		append_token(tkns, DQ_STRING, lexeme);
		free(lexeme);
	}
	else if (c == '\'')
	{
		lexeme = read_quoted(s, src, '\'');
		append_token(tkns, SQ_STRING, lexeme);
		free(lexeme);
	}
}

void	tkn_opt_word(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '-')
	{
		if (is_next(&(s->cur), src, 'n'))
			append_token(tkns, OPTION_N, "-n");
		else
			perror("Invalid option: only -n is allowed.");
	}
	else if (ft_isalnum(c) || issymbol(c))
	{
		lexeme = read_identifier(s, src);
		if (is_keyword(lexeme) != -1)
			append_token(tkns, is_keyword(lexeme), lexeme);
		else
			append_token(tkns, IDENTIFIER, lexeme);
		free(lexeme);
	}	
}
