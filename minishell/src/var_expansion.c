/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/12 16:46:19 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * Traverses the tree and expands the variables
******************************************************************************/
void	expand_var_tree(t_t_node **root, t_vars *vars, t_info *info)
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
void	expand_var_list(t_token_list *tokens, t_vars *vars, t_info *info)
{
	t_token_node	*node;
	char			*old_lexeme;

	if (!tokens || !vars)
		return ;
	node = tokens->head;
	while (node)
	{
		// if (node->token->type == TKN_EXIT_STATUS)
		// 	expand_exitstatus(node, info);
		// else if (node->token->type == TKN_ENV_VAR)
		// 	expand_envvar(node, vars);
		if (node->token->type == TKN_WORD || node->token->type == TKN_VAR_VALUE)
		{
			old_lexeme = node->token->lexeme;
			node->token->lexeme = expand_qstring(node->token->lexeme,
					vars, info);
			free(old_lexeme);
		}
		node = node->next;
	}
}

/*****************************************************************************
 * Exchanges the environment variable for its value in a given node
 * Assumes the token type of the node is TKN_ENV_VAR
******************************************************************************/
// void	expand_envvar(t_token_node *node, t_vars *vars)
// {
// 	t_vars	*var;
// 	char	*old_lexeme;

// 	if (!node || !vars)
// 		return ;
// 	var = find_vars(vars, node->token->lexeme);
// 	old_lexeme = node->token->lexeme;
// 	free(old_lexeme);
// 	if (var)
// 		node->token->lexeme = ft_strdup(var->value);
// 	else
// 		node->token->lexeme = ft_strdup("");
// 		// perror("Variable not found"); //This is a syntax error and should stop and clean everything
// 		// return ; //Clear memory
// 		// // !!!!!!!!!!!!!!!!!! It's actually not a syntax error, it just prints nothing
// 	node->token->type = TKN_WORD;
// }

/*****************************************************************************
 * Exchanges the $? for its value in a given node
 * Assumes the token type of the node is TKN_EXIT_STATUS
******************************************************************************/
// void	expand_exitstatus(t_token_node *node, t_info *info)
// {
// 	int		exit_status;
// 	char	*old_lexeme;

// 	if (!node || !info)
// 		return ;
// 	exit_status = info->last_return_code;
// 	old_lexeme = node->token->lexeme;
// 	free(old_lexeme);
// 	node->token->lexeme = ft_itoa(exit_status);
// 	node->token->type = TKN_WORD;
// }

/*****************************************************************************
 * Builds a new string by expanding variables and exit status 
 * 
 * Expands everything that is not in single quotes
******************************************************************************/
char	*expand_qstring(char *s, t_vars *vars, t_info *info)
{
	char	*result;
	int		len;
	bool	in_single;
	int		i;
	int		res_i;
	char	*var_name;
	t_vars	*var;

	len = qstr_exp_len(s, vars, info);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	in_single = false;
	i = 0;
	res_i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		else if (s[i] == '\"')
			i++;
		else if (!in_single && s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				put_exitstatus(&result, info, &res_i);
				i++;
			}
			else if (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			{
				var_name = get_var_name(s, i - 1);
				var = find_vars(vars, var_name);
				if (var)
					put_var(&result, var->value, &res_i);
				else
					put_var(&result, "", &res_i);
				i += ft_strlen(var_name);
				free(var_name);
			}
			else
				result[res_i++] = '$';
		}
		else
			result[res_i++] = s[i++];
	}
	result[res_i] = '\0';
	return (result);
}

/*****************************************************************************
 * Expands all variables in a string while respecting the rest of the characters
 * Returns a new string with all the vars replaced
******************************************************************************/
char	*expand_string(char *string, t_vars *vars)
{
	int		i;
	char	*result;
	char	*tmp;
	int		len;

	if (!string || !vars)
		return (NULL);
	if (!ft_strnstr(string, "$", ft_strlen(string)))
		return (ft_strdup(string));
	i = get_position(string, '$');
	result = ft_strdup(string);
	if (!result)
		return (NULL);
	len = (int)ft_strlen(string);
	while (i < len)
	{
		tmp = result;
		result = expand_one_string(tmp, vars);
		free(tmp);
		if (!result)
			return (NULL);
		i = get_position(result, '$');
		len = (int)ft_strlen(result);
	}
	return (result);
}

/*****************************************************************************
* Expands a variable in a double quoted string
* Returns a string with the var replaced
* 
* aux[0] = start
* aux[1] = var_name
* aux[2] = start + var value
* aux[3] = rest
* 
******************************************************************************/
char	*expand_one_string(char *string, t_vars *vars)
{
	int		i;
	char	*result;
	char	**aux;
	t_vars	*var;

	i = get_position(string, '$');
	aux = malloc(5 * sizeof(char *));
	if (!aux)
		return (NULL);
	aux[0] = ft_substr(string, 0, i);
	aux[1] = get_var_name(string, i);
	var = find_vars(vars, aux[1]);
	if (!var || !var->value)
		aux[2] = ft_strjoin(aux[0], "");
	else
		aux[2] = ft_strjoin(aux[0], var->value);
	aux[3] = ft_substr(string, i + 1 + ft_strlen(aux[1]),
			ft_strlen(string)- i - 1 - ft_strlen(aux[1]));
	aux[4] = NULL;
	result = ft_strjoin(aux[2], aux[3]);
	clear_array(aux);
	return (result);
}

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

char	*remove_quotes(char *string)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(string);
	result = malloc(len + 1);
	i = 0;
	j = 0;
	while (string[i])
	{
		if (string[i] != '\"' && string[i] != '\'')
			result[j++] = string[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
