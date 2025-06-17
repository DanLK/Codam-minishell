/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/17 15:45:21 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 15:46:06 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
 *  Transforms the token list on the command node into an array containing 
 * the parameters to echo and calls the echo_builtin function
 * 
 * 
 * Maybe the ignoring should happen inside the builtin!!!
*******************************************************************************/
int	execute_echo(t_token_list *tokens)
{
	char			**params;
	int				len;
	int				i;
	int				exit_st;
	t_token_node	*node;

	if (!tokens)
		return (1);
	len = len_token_list(tokens);
	params = (char **)malloc((len) * sizeof(char *));
	if (!params)
		return (1);
	params[len - 1] = NULL;
	if (len > 1)
		node = tokens->head->next;
	i = 0;
	while (len > 1 && node != NULL && (i < len - 1))
	{
		params[i] = ft_strdup(node->token->lexeme);
		node = node->next;
		i++;
	}
	exit_st = echo_builtin(params);
	clear_array(params);
	return (exit_st);
}

int	execute_cd(t_token_list *tokens, t_vars *vars)
{
	if (!tokens || !vars)
		return (1);
	if (!tokens->head->next)
		return (cd_builtin(NULL, vars));
	if (tokens->head->next->next)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (cd_builtin(tokens->head->next->token->lexeme, vars));
}

static int	check_exit_code(char *exit_code)
{
	int	i;

	i = 0;
	if (!exit_code || exit_code[i] == '\0')
		return (0);
	while (exit_code[i] && (exit_code[i] == '+' || exit_code[i] == '-'))
		i++;
	while (exit_code[i] != '\0')
	{
		if (!ft_isdigit(exit_code[i]))
			return (0);
		i++;
	}
	return (1);
}

int	execute_exit(t_token_list *tokens, t_vars *vars, t_info *info)
{
	int	exit_code;

	exit_code = 0;
	if (!tokens || !vars)
		return (1);
	if (!tokens->head->next)
		return (exit_builtin(vars, info, info->last_return_code));
	if (tokens->head->next->next)
	{
		ft_putendl_fd("Minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	else
	{
		if (check_exit_code(tokens->head->next->token->lexeme) == 1)
			exit_code = ft_atoi(tokens->head->next->token->lexeme);
		else
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(tokens->head->next->token->lexeme, STDERR_FILENO);
			ft_putendl_fd(": exit: numeric argument required", STDERR_FILENO);
			return (exit_builtin(vars, info, 2));
		}
	}
	return (exit_builtin(vars, info, exit_code));
}
