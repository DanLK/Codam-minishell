/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/17 11:29:28 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/15 16:18:14 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;
	char			*input;

	// Special case: \"\"\"\"echo\" hello\'ho ho\'\"\"\"

	input = "echo \" hello\"";
	ft_printf("Scanning input: \"%s\" \n\n", input);
	list = scan(input);
	print_token_list(list);
	clear_token_list(list);

	return (0);
}
