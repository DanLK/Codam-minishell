/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executioner.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 13:36:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/22 16:44:03 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND
*******************************************************************************/
int	execute_command(t_t_node **root, t_vars *vars)
{
	t_token_list	*tokens;

	if (!root)
		return (125); //Not sure what to return here
	tokens = (*root)->tokens;
	if (is_builtin_type(tokens->head->token->type))
		return (execute_builtin(root, vars));
	return (125); //For now
}

/*******************************************************************************
 *  Assuming the root node is of type P_COMMAND and the head of the
 * token list is one of the builtins
*******************************************************************************/
int	execute_builtin(t_t_node **root, t_vars *vars)
{
	t_token_list	*tokens;
	enum e_Type		type;
	char			*str;


	if (!root)
		return (125);
	tokens = (*root)->tokens;
	type = tokens->head->token->type;
	if (type == TKN_ECHO)
		return (1); // temporarily
	if (type == TKN_CD)
	{
		str = tokens->head->next->token->lexeme;
		cd_builtin(str, vars);
		return (2); // Temporarily
	}
	if (type == TKN_PWD)
	{
		//TO DO: Check that the list only contains pwd --->>> NOT NECESSARY
		pwd_builtin();
		return (3); // Temporarily
	}
	if (type == TKN_EXPORT)
	{
		return (4); //For now, further processing of the variable name and variable value are needed
	}
	if (type == TKN_UNSET)
	{
		str = tokens->head->next->token->lexeme;
		unset_builtin(&vars, str);
		return (5); // Temporarily
	}
	if (type == TKN_ENV)
	{
		env_builtin(vars);
		return (6);
	}
	if (type == TKN_EXIT)
	{
		exit_builtin(""); // For now
		return (7);
	}
	return (125); //For now
}
