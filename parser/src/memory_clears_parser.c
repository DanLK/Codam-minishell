/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_clears_parser.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/03 15:39:13 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/27 17:08:08 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clear_subtree(t_t_node *root)
{
	if (!root)
		return ;
	clear_token_list(root->tokens);
	clear_redirs(root->redirs);
	clear_subtree(root->left);
	clear_subtree(root->right);
	free(root);
}

void	clear_array(char **words)
{
	char	*word;
	char	*tmp;
	int		i;

	if (!words)
		return ;
	i = 0;
	word = words[0];
	while(word)
	{
		i++;
		tmp = words[i];
		free(word);
		word = tmp;
	}
	free(words);
}
