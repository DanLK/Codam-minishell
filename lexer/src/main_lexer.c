/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/17 11:29:28 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 15:12:30 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;
	char			*input;

	input = "echo \"hello '\"'house'of>cards";
	ft_printf("Scanning input: \"%s\" \n\n", input);
	list = scan(input);
	print_token_list(list);
	clear_token_list(list);
	return (0);
}
