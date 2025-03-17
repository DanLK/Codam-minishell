/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 16:58:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/17 14:13:47 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include "libft.h"

enum e_Type
{
	// Single character tokens
	LEFT_PAREN,
	RIGHT_PAREN,
	// Builtins
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	// Options (for example -n)
	OPTION,
	// Redirections
	RED_INPUT,
	RED_OUTPUT,
	HEREDOC,
	RED_OUT_APP,
	// Operators
	PIPE,
	// Exit status ($?)
	EXIT_STATUS,
	// Parameter Expansion ($)
	ENV_VAR,
	// Path
	FILE_PATH,
	// Literals
	SQ_STRING,
	DQ_STRING,
	//Whitespace
	WHITESPACE,
	//EOF
	EOF
};

typedef struct token
{
	enum e_Type	type;
	char		*lexeme;
}		t_token;

t_token	**scan(char *source);

#endif
