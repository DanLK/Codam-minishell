/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/21 16:07:58 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*****************************************************************************
 * Traverses the tree and expands the variables
******************************************************************************/
void	expand_var_tree(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	if (!root || !*root | !vars)
		return ;
	expand_var_list((*root)->tokens, vars, info);
	if ((*root)->left)
		expand_var_tree(&(*root)->left, vars, info);
	if ((*root)->right)
		expand_var_tree(&(*root)->right, vars, info);
}

/*****************************************************************************
 * Expands the necessary variables in a token list 
 * 
 * Expands the nodes of type ENV_VAR and the nodes of type DQ_STRING
 * 
 * For the WORD and Q_STRING nodes, it calls expand_qstring
 * 
******************************************************************************/
void	expand_var_list(t_token_list *tokens, t_vars *vars, t_shell_info *info)
{
	t_token_node	*node;
	char			*old_lexeme;

	if (!tokens || !vars)
		return ;
	node = tokens->head;
	while (node)
	{
		if (node->token->type == TKN_EXIT_STATUS)
			expand_exitstatus(node, info);
		else if (node->token->type == TKN_ENV_VAR)
			expand_envvar(node, vars);
		else if (node->token->type == TKN_Q_STRING
			|| node->token->type == TKN_WORD)
		{
			old_lexeme = node->token->lexeme;
			node->token->lexeme = expand_qstring(node->token->lexeme, vars, info);
			free(old_lexeme);
		}
		node = node->next;
	}
}

/*****************************************************************************
 * Exchanges the environment variable for its value in a given node
 * Assumes the token type of the node is TKN_ENV_VAR
******************************************************************************/
void	expand_envvar(t_token_node *node, t_vars *vars)
{
	t_vars	*var;
	char	*old_lexeme;

	if (!node || !vars)
		return ;
	var = find_vars(vars, node->token->lexeme);
	if (var)
	{
		// ft_printf("[expand_envvar] var_name = %s\n", var->value);
		old_lexeme = node->token->lexeme;
		free(old_lexeme);
		node->token->lexeme = ft_strdup(var->value); 
	}
	else
		node->token->lexeme = ft_strdup("");
		// perror("Variable not found"); //This is a syntax error and should stop and clean everything
		// return ; //Clear memory
		// // !!!!!!!!!!!!!!!!!! It's actually not a syntax error, it just prints nothing
	node->token->type = TKN_WORD;
}

/*****************************************************************************
 * Exchanges the $? for its value in a given node
 * Assumes the token type of the node is TKN_EXIT_STATUS
******************************************************************************/
void	expand_exitstatus(t_token_node *node, t_shell_info *info)
{
	int		exit_status;
	char	*old_lexeme;

	if (!node || !info)
		return ;
	exit_status = info->last_return_code;
	old_lexeme = node->token->lexeme;
	free(old_lexeme);
	node->token->lexeme = ft_itoa(exit_status); 
	node->token->type = TKN_WORD;
}

/*****************************************************************************
 * Builds a new string by expanding variables and exit status that are in quotes
******************************************************************************/
char	*expand_qstring(char *s, t_vars *vars, t_shell_info *info)
{
	char	*result;
	int		len;
	bool	in_double;
	int		i;
	int		res_i;
	char	*var_name;
	t_vars	*var;

	// ft_printf("[expand_qstring] Entering function...\n");
	len = qstr_exp_len(s, vars, info);
	// ft_printf("[expand_qstring] Expanded string len: %d\n", len);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	in_double = false;
	i = 0;
	res_i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		else if (in_double && s[i] == '$')
		{
			i++;
			// ft_printf("[expand_qstring] Found a $...\n");
			if (s[i] == '?')
			{
				put_exitstatus(&result, info, &res_i);
				i++;
			}
			else if (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			{
				var_name = get_var_name(s, i - 1);
				// ft_printf("[expand_qstring] var_name: [%s]\n", var_name);
				var = find_vars(vars, var_name);
				// ft_printf("[expand_qstring] var_value: [%s]\n", var->value);
				if (var)
				{
					put_var(&result, var->value, &res_i);
					// ft_printf("[expand_qstring] After copying var value  res_i = [%d]\n", res_i);
				}
				else
					put_var(&result, "", &res_i);
				i += ft_strlen(var_name);
				free(var_name);
			}
			else //It's just $
			{
				result[res_i++] = '$';
				// result[res_i++] = s[i++];
			}
		}
		else
		{
			result[res_i++] = s[i++];
			// ft_printf("[expand_qstring] result[%d] = [%c]\n", res_i - 1, result[res_i -1]);
		}
	}
	// ft_printf("[expand_qstring] result after loop: %s\n", result);
	result[res_i] = '\0';
	return (result);
}

/*****************************************************************************
 * Expands all variables that are in between double quotes
 * Returns a new string with all the vars replaced
******************************************************************************/
// char	*expand_qstring(char *string, t_vars *vars)
// {
// 	char	*result;
// 	if (!string || !vars)
// 		return (NULL);
// 	if (!ft_strnstr(string, "$", ft_strlen(string)))
// 	{
// 		result = remove_quotes(string);
// 		return (result);
// 	}
// 	return (ft_strdup(string));
// }

/*****************************************************************************
 * Expands all variables in a double quoted string
 * Returns a new string with all the vars replaced
******************************************************************************/
// char	*expand_dqstring(char *string, t_vars *vars)
// {
// 	int		i;
// 	char	*result;
// 	char	*tmp;
// 	int		len;
// 	// bool	in_quotes;

// 	if (!string || !vars)
// 		return (NULL);
// 	if (!ft_strnstr(string, "$", ft_strlen(string)))
// 		return (ft_strdup(string));
// 	i = get_position(string, '$');
// 	result = ft_strdup(string);
// 	if (!result)
// 		return (NULL);
// 	len = (int)ft_strlen(string);
// 	while (i < len)
// 	{
// 		tmp = result;
// 		result = expand_one_dqstring(tmp, vars);
// 		free(tmp);
// 		if (!result)
// 			return (NULL);
// 		i = get_position(result, '$');
// 		len = (int)ft_strlen(result);
// 	}
// 	return (result);
// }

// /*****************************************************************************
//  * Expands a variable in a double quoted string
//  * Returns a string with the var replaced
//  * 
//  * aux[0] = start
//  * aux[1] = var_name
//  * aux[2] = start + var value
//  * aux[3] = rest
//  * 
// ******************************************************************************/
// char	*expand_one_dqstring(char *string, t_vars *vars)
// {
// 	int		i;
// 	char	*result;
// 	char	**aux;
// 	t_vars	*var;
	
// 	i = get_position(string, '$');
// 	ft_printf("[expand_one_dqstring] $-position: %d\n", i);
// 	aux = malloc(5 * sizeof(char *));
// 	if (!aux)
// 		return (NULL);
// 	aux[0] = get_start_trim_quotes(string, i);
// 	ft_printf("[expand_one_dqstring] start: %s\n", aux[0]);
// 	aux[1] = get_var_name(string, i);
// 	var = find_vars(vars, aux[1]);
// 	if (!var || !var->value)
// 	{
// 		perror("Variable not found"); //Clean up?
// 		exit(EXIT_FAILURE);// JUST FOR NOWWW!!!!
// 		aux[2] = ft_strjoin(aux[0], ""); //At the moment replacing with the empty string
// 	}
// 	else
// 		aux[2] = ft_strjoin(aux[0], var->value);
// 	aux[3] = ft_substr(string, i + 1 + ft_strlen(aux[1]),
// 				ft_strlen(string)- i - 1 - ft_strlen(aux[1]));
// 	aux[4] = NULL;
// 	result = ft_strjoin(aux[2], aux[3]);
// 	clear_array(aux);
// 	return (result);
// }

// char	*get_start_trim_quotes(char *string, size_t len)
// {
// 	char	*result;
// 	int		i;
// 	int		j;

// 	result = malloc(len);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (string[i])
// 	{
// 		if (string[i] != '\"')
// 			result[j++] = string[i];
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

// char	*remove_quotes(char *string)
// {
// 	char	*result;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_strlen(string);
// 	result = malloc(len);
// 	i = 0;
// 	j = 0;
// 	while (string[i])
// 	{
// 		if (string[i] != '\"')
// 			result[j++] = string[i];
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }