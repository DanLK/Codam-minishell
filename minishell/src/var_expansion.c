/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 09:49:04 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/21 17:19:09 by dloustal      ########   odam.nl         */
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
	expand_redir_files((*root)->redirs, vars, info);
	if ((*root)->left)
		expand_var_tree(&(*root)->left, vars, info);
	if ((*root)->right)
		expand_var_tree(&(*root)->right, vars, info);
}

/*****************************************************************************
 * Expands the necessary variables in a token list 
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
		if (node->token->type == TKN_WORD || node->token->type == TKN_VAR_VALUE
			|| node->token->type == TKN_VAR_NAME)
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
 * Expands the necessary variables in a redirs list
 * 
******************************************************************************/
void	expand_redir_files(t_redir_node **red_head, t_vars *v, t_info *info)
{
	t_redir_node	*redir;
	char			*old_file;

	if (!red_head || !v || !info)
		return ;
	redir = *red_head;
	while (redir)
	{
		if (redir->type == TKN_FILE_PATH)
		{
			old_file = redir->file;
			redir->file = expand_qstring(redir->file,
					v, info);
			free(old_file);
		}
		redir = redir->next;
	}
}

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

// /************************************************************************
//  * Builds a new string by expanding variables and exit status 
//  * 
//  * Expands everything that is not in single quotes
// *************************************************************************/
// char	*expand_qstring_cpy(char *s, t_vars *vars, t_info *info)
// {
// 	char	*result;
// 	int		len;
// 	bool	in_single;
// 	bool	in_double;
// 	int		i;
// 	int		res_i;
// 	char	*var_name;
// 	t_vars	*var;

// 	if (!s)
// 		return (NULL);
// 	len = qstr_exp_len(s, vars, info);
// 	result = malloc((len + 1) * sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	in_single = false;
// 	in_double = false;
// 	i = 0;
// 	res_i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'')
// 		{
// 			if (in_double)
// 				result[res_i++] = s[i];
// 			else
// 				in_single = !in_single;
// 			i++;
// 			continue ;
// 		}
// 		else if (s[i] == '\"')
// 		{
// 			if (in_single)
// 				result[res_i++] = s[i];
// 			else
// 				in_double = !in_double;
// 			i++;
// 		}
// 		else if (!in_single && s[i] == '$')
// 		{
// 			i++;
// 			if (s[i] == '?')
// 			{
// 				put_exitstatus(&result, info, &res_i);
// 				i++;
// 			}
// 			else if (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
// 			{
// 				var_name = get_var_name(s, i - 1);
// 				var = find_vars(vars, var_name);
// 				if (var)
// 					put_var(&result, var->value, &res_i);
// 				else
// 					put_var(&result, "", &res_i);
// 				i += ft_strlen(var_name);
// 				free(var_name);
// 			}
// 			else
// 				result[res_i++] = '$';
// 		}
// 		else
// 			result[res_i++] = s[i++];
// 	}
// 	result[res_i] = '\0';
// 	return (result);
// }
