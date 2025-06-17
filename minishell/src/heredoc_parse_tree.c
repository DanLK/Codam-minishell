/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parse_tree.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 13:49:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 18:11:45 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
 * Traverses the tree (DFS) in search for heredocs
*******************************************************************************/
void	parse_hd_tree(t_t_node **root, t_vars *vars, t_info *info)
{
	if (!root)
		return ;
	if ((*root)->left)
		parse_hd_tree(&(*root)->left, vars, info);
	if ((*root)->right)
		parse_hd_tree(&(*root)->right, vars, info);
	parse_hd_node(root, vars, info);
}

/*******************************************************************************
 * Does a pass through the redirs list to find the heredocs
*******************************************************************************/
void	parse_hd_node(t_t_node **root, t_vars *vars, t_info *info)
{
	t_redir_node	*cur;

	if (!root || !vars || !info)
		return ;
	if ((*root)->redirs == NULL)
		return ;
	cur = *((*root)->redirs);
	while (cur)
	{
		if (cur->type == TKN_HEREDOC)
			parse_hd(cur, vars, info);
		cur = cur->next->next;
	}
}

/*******************************************************************************
 * Function will truncate a temp file if called. Should be called when sigint 
 * is pressed by the user and prevents the contents of the file from 
 * being printed
*******************************************************************************/
void	sigint_clean(int fd, char *file_name)
{
	close(fd);
	fd = open(file_name, O_WRONLY | O_TRUNC);
	if (fd < 0)
		return (free(file_name));
	close(fd);
}
