/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:28 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/04 16:33:11 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
{
	t_token_list	*list;
	char			*input;

	input = "\"hello $USER\"\'hi $USER\'morewords";
	ft_printf("Scanning input: \"%s\" \n\n", input);
	list = scan(input);
	print_token_list(list);
	clear_token_list(list);
	return (0);
}
