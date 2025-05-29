/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 13:49:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/29 12:14:34 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

/*******************************************************************************
 * Traverses the tree (DFS) in search for heredocs
*******************************************************************************/
void	parse_hd_tree(t_t_node **root, t_vars *vars, t_shell_info *info)
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
void	parse_hd_node(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	t_redir_node	*cur;
	char			*file_name;

	if (!root || !vars || !info)
		return ;
	if ((*root)->redirs == NULL)
		return ;
	cur = *((*root)->redirs);
	while (cur)
	{
		if (cur->type == TKN_HEREDOC)
		{
			file_name = parse_hd(remove_quotes(cur->next->file), vars, info);
			if (file_name)
			cur->next->file = file_name;
		}
		cur = cur->next->next;
	}
}

/*******************************************************************************
 * Function will truncate a temp file if called. Should be called when sigint 
 * is pressed by the user and prevents the contents of the file from 
 * being printed
*******************************************************************************/
static void sigint_cleanup(int fd, char *file_name)
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
// void	parse_hd_cpy(char *eof, t_vars *vars, t_shell_info *info)
// {
// 	int		fd;
// 	char	*input;
// 	char	*file_name;

// 	init_heredoc();
// 	sim_press_hook();
// 	heredoc_action();
// 	file_name = ft_strjoin(".tmp_heredoc", ft_itoa(info->hd_count));
// 	// ft_printf("[parse_hd] tmp filename: %s\n", file_name);
// 	fd = open(file_name, O_WRONLY | O_CREAT, 0644); //I don't know what the numbers mean
// 	if (fd < 0)
// 		return (free(file_name));
// 	input = expand_string(readline("heredoc> "), vars); // VAR EXPANSIONS
// 	if (!input)
// 	{
// 		free(file_name);
// 		heredoc_cleanup(fd);
// 		info->hd_count++;
// 		return ;
// 	} //SIGNALS
// 	// if (ft_strcmp(input, eof) == 0)
// 	// {
// 	// 	info->hd_count++;
// 	// 	close(fd);
// 	// 	heredoc_cleanup(fd);
// 	// 	return (free(file_name), free(input));
// 	// }
// 	if (get_signal_received() == SIGINT)
// 		return (info->hd_count++, sigint_cleanup(fd, file_name), heredoc_cleanup(fd));
// 	else
// 	{
// 		while (input)
// 		{
// 			if (ft_strcmp(input, eof) == 0)
// 			{
// 				info->hd_count++;
// 				close(fd);
// 				heredoc_cleanup(fd);
// 				return (free(file_name), free(input));
// 			}
// 			else
// 			{
// 				write(fd, input, ft_strlen(input));
// 				write(fd, "\n", 1);
// 				input = expand_string(readline("heredoc> "), vars);
// 				if (!input)
// 					return (info->hd_count++, heredoc_cleanup(fd), free(file_name));
// 				if (get_signal_received() == SIGINT)
// 					return (info->hd_count++, sigint_cleanup(fd, file_name), free(file_name), heredoc_cleanup(fd));
// 			}
// 		}
// 	}
// }

char	*parse_hd(char *eof, t_vars *vars, t_shell_info *info)
{
	int		fd;
	char	*input;
	char	*file_name;
	char	*index;

	init_heredoc();
	sim_press_hook();
	heredoc_action();
	index = ft_itoa(info->hd_count);
	file_name = ft_strjoin(".tmp_heredoc", index);
	fd = open(file_name, O_WRONLY | O_CREAT, 0644); //I don't know what the numbers mean
	if (fd < 0)
		return (free(file_name), NULL);
	while (1)
	{
		input = expand_string(readline("heredoc> "), vars);
		if (get_signal_received() == SIGINT)
		{
			info->hd_count++;
			free(index);
			return (sigint_cleanup(fd, file_name), free(file_name), heredoc_cleanup(fd), NULL);
		}
		if (!input)
			return (info->hd_count++, heredoc_cleanup(fd), free(file_name), free(index), NULL);
		if (ft_strcmp(input, eof) == 0)
		{
			info->hd_count++;
			close(fd);
			heredoc_cleanup(fd);
			return (free(input), free(index), file_name);
		}
		else
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
	}
}
