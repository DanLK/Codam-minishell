/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:11:14 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/05 10:50:21 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	if_redir_out(t_token_list *tkns, char *src, t_scanner *s)
{
	char	*lexeme;

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
	if (lexeme && ft_strlen(lexeme) > 0)
		append_token(tkns, TKN_FILE_PATH, lexeme);
	free(lexeme);
}

void	redir_tkn(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '>')
		if_redir_out(tkns, src, s);
	else if (c == '<')
	{
		if (is_next(&(s->cur), src, '<'))
			append_token(tkns, TKN_HEREDOC, "<<");
		else
		{
			append_token(tkns, TKN_REDIR_IN, "<");
			(s->start)++;
			lexeme = read_filepath(s, src);
			if (lexeme && ft_strlen(lexeme) > 0)
				append_token(tkns, TKN_FILE_PATH, lexeme);
			free(lexeme);
		}
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
		lexeme = read_quoted(s, src);
		append_token(tkns, TKN_Q_STRING, lexeme);
		free(lexeme);
	}
	else if (c == '\'')
	{
		lexeme = read_quoted(s, src);
		append_token(tkns, TKN_Q_STRING, lexeme);
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
	substr = ft_substr(src, scanner->start + 1,
			scanner->cur - scanner->start - 1);
	return (substr);
}

void	tkn_opt_word(t_token_list *tkns, char *src, t_scanner *s, char c)
{
	char	*lexeme;

	if (c == '-')
	{
		lexeme = read_options(s, src);
		if (!lexeme)
			perror("Invalid options");
		else if (ft_strlen(lexeme) == 1)
			append_token(tkns, TKN_WORD, lexeme);
		else
			append_token(tkns, TKN_OPTION, lexeme);
		free(lexeme);
	}
	else if (ft_isalnum(c) || issymbol(c) || c == ':')
	{
		lexeme = read_quoted(s, src);
		if (is_keyword(lexeme) != -1)
			append_token(tkns, is_keyword(lexeme), lexeme);
		else
			append_token(tkns, TKN_WORD, lexeme);
		free(lexeme);
	}
}
