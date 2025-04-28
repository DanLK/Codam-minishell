/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_identifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 12:11:14 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/28 11:37:28 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
			append_token(tkns, TKN_REDIR_OUT_APP, ">>");
			s->start += 2;
		}
		else
		{
			append_token(tkns, TKN_REDIR_OUT, ">");
			(s->start)++;
		}
		lexeme = read_filepath(s, src);
		append_token(tkns, TKN_FILE_PATH, lexeme);
		free(lexeme);
	}
	else if (c == '<')
	{
		if (is_next(&(s->cur), src, '<'))
			append_token(tkns, TKN_HEREDOC, "<<");
		else
			append_token(tkns, TKN_REDIR_IN, "<");
	}
}

void	tkn_quote(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '$')
	{
		if (is_next(&(s->cur), src, '?'))
			append_token(tkns, TKN_EXIT_STATUS, "$?");
		else
		{
			lexeme = tkn_env_var(src, s);
			append_token(tkns, TKN_ENV_VAR, lexeme);
			free(lexeme);
		}
	}
	else if (c == '"')
	{
		lexeme = read_quoted(s, src, '"');
		append_token(tkns, TKN_DQ_STRING, lexeme);
		free(lexeme);
	}
	else if (c == '\'')
	{
		lexeme = read_quoted(s, src, '\'');
		append_token(tkns, TKN_SQ_STRING, lexeme);
		free(lexeme);
	}
}

char	*tkn_env_var(char *src, t_scanner *scanner)
{
	char	*substr;

	if (!src || scanner->cur >= (int)ft_strlen(src))
		return (NULL);
	while (!is_special_char(src[scanner->cur]) && src[scanner->cur])
		scanner->cur += 1;
	substr = ft_substr(src, scanner->start + 1, scanner->cur - scanner->start - 1);
	return (substr);
}

void	tkn_opt_word(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '-')
	{
		lexeme = read_options(s, src);
		if (!lexeme || ft_strlen(lexeme) == 1)
			perror("Invalid options");
		else
			append_token(tkns, TKN_OPTION, lexeme);
		free(lexeme);
	}
	else if (ft_isalnum(c) || issymbol(c))
	{
		lexeme = read_identifier(s, src);
		if (is_keyword(lexeme) != -1)
			append_token(tkns, is_keyword(lexeme), lexeme);
		else
			append_token(tkns, TKN_WORD, lexeme);
		free(lexeme);
	}
}

char	*read_options(t_scanner *scanner, char *src)
{
	char	*option;
	int		start;
	char	c;

	if (!scanner || !src || scanner->cur >= (int)ft_strlen(src))
		return (NULL);
	start = scanner->start;
	c = src[(scanner->cur)];
	while (c && ft_isalpha(c))
	{
		scanner->cur += 1;
		c = src[scanner->cur];
	}
	option = ft_substr(src, start, (scanner->cur) - start);
	return (option);
}
