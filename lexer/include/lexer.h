/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 16:58:50 by dloustal      #+#    #+#                 */
/*   Updated: 2025/03/14 18:03:14 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>
# include "../../libft/libft.h"

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
	// Redirections
	RED_INPUT,
	RED_OUTPUT,
	HEREDOC,
	RED_OUT_APP,
	// Operators
	PIPE,
	// Exit status
	EXIT_STATUS,
	// Parameter Expansion ($)
	PARAM_EXPANSION,
	// Path
	PATH,
	// Literals
	STRING,
	//EOF
	EOF
};

typedef struct token
{
	enum e_Type	type;
	char		*lexeme;
}		t_token;

#endif
