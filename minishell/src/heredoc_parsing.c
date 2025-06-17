/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:41 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/17 14:43:11 by rojornod         ###   ########.fr       */
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
static void	sigint_cleanup(int fd, char *file_name)
{
	close(fd);
	fd = open(file_name, O_WRONLY | O_TRUNC);
	if (fd < 0)
		return (free(file_name));
	close(fd);
}

/*******************************************************************************
 * Creates the heredoc prompt and does the reading, creating file and 
 * parsing the input
 * 
 * It stops when it hits the specified eof string
*******************************************************************************/
void	parse_hd(t_redir_node *cur, t_vars *vars, t_info *info)
{
	int		fd;
	char	*input;
	char	*file_name;
	char	*index;
	char	*eof;
	char	*old_file;
	bool	quoted_eof;

	init_heredoc();
	sim_press_hook();
	heredoc_action();
	index = ft_itoa(info->hd_count);
	file_name = ft_strjoin("/tmp/.tmp_heredoc", index);
	fd = open(file_name, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (free(file_name));
	if (cur->next->file[0] && (cur->next->file[0] == '"'
			|| cur->next->file[0] == '\''))
		quoted_eof = true;
	else
		quoted_eof = false;
	eof = remove_quotes(cur->next->file);
	while (1)
	{
		if (quoted_eof)
			input = readline("heredoc> ");
		else
			input = expand_qstring(readline("heredoc> "), vars, info);
		if (get_signal_received() == SIGINT)
		{
			info->hd_count++;
			old_file = cur->next->file;
			cur->next->file = ft_strdup(file_name);
			return (free(old_file), free(index), free(input),
				sigint_cleanup(fd, file_name), free(eof), free(file_name),
				heredoc_cleanup(fd));
		}
		if (!input)
		{
			old_file = cur->next->file;
			cur->next->file = ft_strdup(file_name);
			return (free(old_file), free(eof), info->hd_count++,
				heredoc_cleanup(fd), free(file_name), free(index));
		}
		if (ft_strcmp(input, eof) == 0)
		{
			info->hd_count++;
			old_file = cur->next->file;
			cur->next->file = ft_strdup(file_name);
			free(old_file);
			close(fd);
			heredoc_cleanup(fd);
			return (free(input), free(index), free(file_name), free(eof));
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}
