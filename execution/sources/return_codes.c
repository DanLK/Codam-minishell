/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_codes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:43:34 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/05 15:59:19 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/includes/minishell.h"

int return_code(t_shell_info *info, int return_code)
{
	if (return_code >= 0 && return_code <= 255)
		info->last_return_code = return_code;
}