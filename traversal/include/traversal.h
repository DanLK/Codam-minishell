/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traversal.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 12:02:07 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/23 14:08:20 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAVERSAL_H
# define TRAVERSAL_H
# include "parser.h"
# include "minishell.h"

// Executioner
int	execute_command(t_t_node **root, t_vars *vars);
int	execute_builtin(t_t_node **root, t_vars *vars);
int	execute_echo(t_token_list *tokens);

#endif
