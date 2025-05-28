/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_identifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/01 12:11:14 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 16:56:46 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
		// ft_printf("[redir_tkn] s->start: %d\n", s->start);
		// ft_printf("[redir_tkn] s->cur: %d\n", s->cur);
		lexeme = read_filepath(s, src);
		// ft_printf("[redir_tkn] lexeme == NULL: %d\n", lexeme == NULL);
		if (lexeme && ft_strlen(lexeme) > 0)
		{
			// ft_printf("[redir_tkn] Attempting to append the file_path node\n");
			append_token(tkns, TKN_FILE_PATH, lexeme);
		}
		// ft_printf("[redir_tkn] We get here safely\n");
		free(lexeme);
	}
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
